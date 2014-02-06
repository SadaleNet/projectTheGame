#include "Rect.h"
#include "../utils/Color.h"
#include "../scenes/SceneRunner_Winapi.h"

#include <objidl.h>
#include <gdiplus.h>
#include <string>
#pragma comment (lib,"Gdiplus.lib")

Gdiplus::Color GdiPlusColor(::Color c){
	return Gdiplus::Color(int(c.a*255), int(c.r*255), int(c.g*255), int(c.b*255));
}

#define RENDER_BUFFER dynamic_cast<const SceneRunner_Winapi*>(this->getScene()->getSceneRunner())->getBuffer()

void ::Rect::render() const{
	//draw border
	Gdiplus::Pen borderPen(GdiPlusColor(this->borderColor), (REAL)this->borderSize);
	RENDER_BUFFER.DrawRectangle(&borderPen, int(this->pos.x), int(this->pos.y), int(this->size.x), int(this->size.y));

	//fill rect
	Gdiplus::SolidBrush brush(GdiPlusColor(this->fillColor));
	RENDER_BUFFER.FillRectangle(&brush, int(this->pos.x), int(this->pos.y), int(this->size.x), int(this->size.y));
}
