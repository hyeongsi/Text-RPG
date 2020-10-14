#pragma once
#include <windows.h>
#include <string>
#include <MMsystem.h>
#include "Digitalv.h"

#pragma comment(lib,"winmm.lib")

using namespace std;

class SoundManager
{
private:
	string effectSoundPath;
	string selectSoundPath;
public:
	SoundManager();
	void PlaySelectSound();
	void PlayEffectSound();

	void PlayGameBGM();
	void PlayMenuBGM();
	void StopBGM();
};

