#include <string>

/**
	Plays sfx once, without repeating.
	Only .wav format is guranteed to be supported in each implementation.
	@param	filePath	the path to the sfx file
	@return	true if success, false else.
*/
bool playSfx(std::string filePath);

/**
	Plays BGM, which loops until another BGM is played, or stopBGM() is called.
	Only .wav format is guranteed to be supported in each implementation.
	@param	filePath	the path to the BGM file
	@return	true if success, false else.
*/
bool playBgm(std::string filePath);

/**
	@return	true if success, false else.
	@see	playBgm()
*/
bool stopBgm();