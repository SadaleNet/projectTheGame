#include "soundPlayer.h"
#include <Windows.h>
#include <vector>
#include <algorithm>
#pragma comment (lib, "Winmm.lib")

bool playSfx(std::string filePath){
	static std::vector<std::string> openedFiles;
	if(std::find(openedFiles.begin(), openedFiles.end(), filePath)==openedFiles.end()){
		//the file is not opened, let's open it now.
		//While it's possible to use "play whatever.wav", it's better to open it so that the file is cached.
		mciSendStringA((std::string("open ")+filePath+" alias "+filePath+"_CACHED wait").data(), NULL, 0, NULL);
		openedFiles.push_back(filePath);
	}
	mciSendStringA((std::string("seek ")+filePath+"_CACHED to start wait").data(), NULL, 0, NULL);
	return mciSendStringA((std::string("play ")+filePath+"_CACHED").data(), NULL, 0, NULL)==0;
}

namespace{ std::string currentPlayingFilePath; }

bool playBgm(std::string filePath){
	//If the same BGM is being played, do not restart the track.
	if(currentPlayingFilePath==filePath)
		return false;
	currentPlayingFilePath = filePath.data();
	//can't figure out how to repeat audiowave with mciSendStringA(). Using PlaySoundA() instead. NB: I've tried "play file repeat"
	return PlaySoundA(filePath.data(), NULL, SND_FILENAME|SND_ASYNC|SND_LOOP)==TRUE;
}

bool stopBgm(){
	currentPlayingFilePath.clear();
	return PlaySoundA(NULL, NULL, NULL)==TRUE;
}
