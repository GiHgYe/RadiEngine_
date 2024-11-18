#pragma once
#include "audio/core/audio_core.h"
#include <string>

class AudioClip
{
public:
	AudioClip();
	~AudioClip();

    FMOD::Sound* fmod_sound() { return fmod_sound_; }

public:
    /// ������Ч�ļ�������AudioClipʵ��,ע��Ĭ����2D���֡�
    /// \param audio_file_path
    /// \return
    static AudioClip* LoadFromFile(std::string audio_file_path);

private:
    FMOD::Sound* fmod_sound_ = nullptr;
};