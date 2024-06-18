#include "pch.h"
// SoundManager.cpp
#include "SoundManager.h"

// 播放指定的音效文件
void SoundManager::PlaySoundFile(const std::wstring& soundFile)
{
    PlaySound(soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

// 播放赢的音效
void SoundManager::PlayWinSound()
{
    PlaySoundFile(L"sound\\win.wav");
}

// 播放输的音效
void SoundManager::PlayLoseSound()
{
    PlaySoundFile(L"sound\\lose2.wav");
}

// 播放开始的音效
void SoundManager::PlayStartSound()
{
    PlaySoundFile(L"sound\\start.wav");
}

// 播放放下棋子的音效
void SoundManager::PlayDownSound()
{
    PlaySoundFile(L"sound\\down.wav");
}

// 播放错误的音效
void SoundManager::PlayWrongSound()
{
    PlaySoundFile(L"sound\\wrong.wav");
}

// 播放悔棋的音效
void SoundManager::PlayRegretSound()
{
	PlaySoundFile(L"sound\\regret.wav");
}

// 播放关闭的音效
void SoundManager::PlayCloseSound()
{
	PlaySoundFile(L"sound\\down.wav");
}