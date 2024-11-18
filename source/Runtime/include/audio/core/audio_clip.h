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
    /// 加载音效文件，创建AudioClip实例,注意默认是2D音乐。
    /// \param audio_file_path
    /// \return
    static AudioClip* LoadFromFile(std::string audio_file_path);

private:
    FMOD::Sound* fmod_sound_ = nullptr;
};