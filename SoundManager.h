// SoundManager.h
#pragma once

#include <mmsystem.h>
#include <string>

#pragma comment(lib, "winmm.lib")

class SoundManager
{
public:
    // 播放音效
    static void PlayWinSound();
    static void PlayLoseSound();
    static void PlayStartSound();
    static void PlayDownSound();
    static void PlayWrongSound();
    static void PlayRegretSound();
    static void PlayCloseSound();

private:
    // 通用播放函数
    static void PlaySoundFile(const std::wstring& soundFile);
};

