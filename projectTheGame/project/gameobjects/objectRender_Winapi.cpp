#define _CRT_SECURE_NO_WARNINGS //Screw you, Microsoft. Don't lure me to break the portability of my code. >:(
#include "Rect.h"
#include "SpriteObject.h"
#include "Text.h"
#include "../utils/utils.h"
#include "../scenes/SceneRunner_Winapi.h"

#include <cstdlib>
#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")


Gdiplus::Color GdiPlusColor(::Color c){
	return Gdiplus::Color(int(c.a*255), int(c.r*255), int(c.g*255), int(c.b*255));
}

#define RENDER_BUFFER dynamic_cast<const SceneRunner_Winapi*>(this->getScene()->getSceneRunner())->getBuffer()

void ::Rect::render() const{
	Vec2 pos = this->getAbsPos();

	//fill rect
	Gdiplus::SolidBrush brush(GdiPlusColor(this->fillColor));
	RENDER_BUFFER.FillRectangle(&brush, int(pos.x), int(pos.y), int(this->size.x), int(this->size.y));

	//draw border
	Gdiplus::Pen borderPen(GdiPlusColor(this->borderColor), (REAL)this->borderSize);
	borderPen.SetAlignment(Gdiplus::PenAlignmentInset);
	//Somehow, without the -1s and +1s below, the border does not cover the edge of the rect.
	RENDER_BUFFER.DrawRectangle(&borderPen, REAL(pos.x-1), REAL(pos.y-1), REAL(this->size.x+1), REAL(this->size.y+1));
}

void SpriteObject::render() const{
	Vec2 pos = this->getAbsPos();

	//NB: Strange. If this line is used, the program caches when the program is closed. Maybe there is some GC in GDI+ ?
	//static std::map<std::string, std::unique_ptr<Image>> imageCache;
	static std::map<std::string, Image*> imageCache;
	static std::map<std::string, TextureBrush*> textureBrushCache;

	//Attempt to render the image from cache. If the image is not in the cache, load it to the cache and retry.
	//TODO: What if the image is not loaded? Apparently, there is no error handling functions provided by GDI+
	while(true){ //makes continue works.
		try{
			//load image from cache
			TextureBrush* pTexture = textureBrushCache.at(this->imagePath);
			//render it
			pTexture->ResetTransform();
			if(this->tileSize==Vec2(0,0)){
				pTexture->TranslateTransform(REAL(pos.x), REAL(pos.y));
				RENDER_BUFFER.FillRectangle(pTexture, REAL(pos.x), REAL(pos.y), REAL(this->size.x), REAL(this->size.y));
			}else{
				Vec2 scale = Vec2(REAL(this->size.x/this->tileSize.x), REAL(this->size.y/this->tileSize.y));
				//NOTE: somehow, adding -ve sign makes tiling works. It is probably due to the strange coord. sys. of GDI+.
				pTexture->TranslateTransform(REAL(pos.x)+REAL(-this->tileIndex.x*this->tileSize.x)*REAL(scale.x),
					REAL(pos.y)+REAL(-this->tileIndex.y*this->tileSize.y)*REAL(scale.y));
				pTexture->ScaleTransform(REAL(scale.x), REAL(scale.y));
				RENDER_BUFFER.FillRectangle(pTexture,
										REAL(pos.x), REAL(pos.y),
										REAL(this->size.x), REAL(this->size.y));
			}
			return; //rendered. Mission accomplished.
		}catch(std::out_of_range&){
			//Load the image to cache, then render it.

			CHAR_TO_CONST_WCHAR_ARRAY(&this->imagePath[0], imagePathWchar);
			
			//cache the image
			imageCache[this->imagePath] = new Image(imagePathWchar);
			textureBrushCache[this->imagePath] = new TextureBrush(imageCache[this->imagePath], WrapModeTile, 0, 0, imageCache[this->imagePath]->GetWidth(), imageCache[this->imagePath]->GetHeight());
			continue; //try again and render it
		}
	}

	/*//Attempt to render the image from cache. If the image is not in the cache, load it to the cache and retry.
	//TODO: What if the image is not loaded? Apparently, there is no error handling functions provided by GDI+
	while(true){ //makes continue works.
		try{
			//load image from cache
			Image* pImage = imageCache.at(this->imagePath);
			//render it
			if(this->tileSize==Vec2(0,0)){
				RENDER_BUFFER.DrawImage(pImage, REAL(pos.x), REAL(pos.y), REAL(this->size.x), REAL(this->size.y));
			}else{
				Gdiplus::RectF rect(REAL(pos.x), REAL(pos.y), REAL(this->size.x), REAL(this->size.y));
				RENDER_BUFFER.DrawImage(pImage, rect,
										REAL(this->tileIndex.x*this->tileSize.x), REAL(this->tileIndex.y*this->tileSize.y),
										REAL(this->tileSize.x), REAL(this->tileSize.y),
										Gdiplus::UnitPixel, NULL, NULL, NULL);
			}
			return; //rendered. Mission accomplished.
		}catch(std::out_of_range&){
			//Load the image to cache, then render it.

			CHAR_TO_CONST_WCHAR_ARRAY(&this->imagePath[0], imagePathWchar);

			//cache the image
			imageCache[this->imagePath] = new Image(imagePathWchar);
			continue; //try again and render it
		}
	}*/

}


void ::Text::render() const{
	Vec2 pos = this->getAbsPos();

	Gdiplus::FontFamily	fontFamily(L"Arial");
	Gdiplus::Font		font(&fontFamily, REAL(this->fontSize), Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::RectF		bounds(REAL(pos.x), REAL(pos.y), REAL(this->size.x), REAL(this->size.y));
	Gdiplus::SolidBrush	brush(GdiPlusColor(this->fontColor));
	Gdiplus::StringFormat format;
	switch(this->align){
		case LEFT:		format.SetAlignment(Gdiplus::StringAlignmentNear);		break;
		case CENTER:	format.SetAlignment(Gdiplus::StringAlignmentCenter);	break;
		case RIGHT:		format.SetAlignment(Gdiplus::StringAlignmentFar);		break;
		default:		assert(false); //should never reach here.
	}

	CHAR_TO_CONST_WCHAR_ARRAY(&this->text[0], textWchar);
	RENDER_BUFFER.DrawString(textWchar, -1, &font, bounds, &format, &brush);
			
}