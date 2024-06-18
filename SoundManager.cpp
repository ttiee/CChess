#include "pch.h"
// SoundManager.cpp
#include "SoundManager.h"

// ����ָ������Ч�ļ�
void SoundManager::PlaySoundFile(const std::wstring& soundFile)
{
    PlaySound(soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

// ����Ӯ����Ч
void SoundManager::PlayWinSound()
{
    PlaySoundFile(L"sound\\win.wav");
}

// ���������Ч
void SoundManager::PlayLoseSound()
{
    PlaySoundFile(L"sound\\lose2.wav");
}

// ���ſ�ʼ����Ч
void SoundManager::PlayStartSound()
{
    PlaySoundFile(L"sound\\start.wav");
}

// ���ŷ������ӵ���Ч
void SoundManager::PlayDownSound()
{
    PlaySoundFile(L"sound\\down.wav");
}

// ���Ŵ������Ч
void SoundManager::PlayWrongSound()
{
    PlaySoundFile(L"sound\\wrong.wav");
}

// ���Ż������Ч
void SoundManager::PlayRegretSound()
{
	PlaySoundFile(L"sound\\regret.wav");
}

// ���Źرյ���Ч
void SoundManager::PlayCloseSound()
{
	PlaySoundFile(L"sound\\down.wav");
}