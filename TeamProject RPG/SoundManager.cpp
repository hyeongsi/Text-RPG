#include "SoundManager.h"

SoundManager::SoundManager()
{
	effectSoundPath = "effectSound.wav";
	selectSoundPath = "selectSound.wav";
}

void SoundManager::PlaySelectSound()
{
	PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);
	PlaySoundA(selectSoundPath.c_str(), NULL, SND_ASYNC);
}

void SoundManager::PlayEffectSound()
{
	PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);
	PlaySoundA(effectSoundPath.c_str(), NULL, SND_ASYNC);
}

void SoundManager::PlayGameBGM()
{
    //"title.mp3"; // 파일 경로 입력
	mciSendString("play title.mp3 repeat", NULL, 0, NULL);
}

void SoundManager::PlayMenuBGM()
{
    // "menu.mp3"; // 파일 경로 입력
	mciSendString("play menu.mp3 repeat", NULL, 0, NULL);
    
}

void SoundManager::StopBGM()
{
	mciSendString("close title.mp3", NULL, 0, NULL);
	mciSendString("close menu.mp3", NULL, 0, NULL);
}
