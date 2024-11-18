#include "audio/core/audio_clip.h"
#include "utils/debug.h"

AudioClip::AudioClip()
{
}

AudioClip::~AudioClip()
{
    if (fmod_sound_ != nullptr) {
        fmod_sound_->release();
        fmod_sound_ = nullptr;
    }
}

AudioClip* AudioClip::LoadFromFile(std::string audio_file_path)
{
    FMOD::Sound* fmod_sound;
    FMOD_RESULT result = AudioCore::CreateSound( audio_file_path.c_str(), FMOD_DEFAULT, nullptr, &fmod_sound);
    if (result != FMOD_OK) {
        LOG_ERROR("AudioCore::CreateSound failed");
        return nullptr;
    }

    AudioClip* audio_clip = new AudioClip();
    audio_clip->fmod_sound_ = fmod_sound;
    return audio_clip;
}
