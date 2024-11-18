#include "audio/core/audio_source.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "utils/debug.h"


AudioSource::AudioSource() :Component() {}

void AudioSource::Set3DMode(bool mode_3d) {
    if (mode_3d) {
        fmod_mode_ = fmod_mode_ | FMOD_3D;
    }
    else {
        if (fmod_mode_ & FMOD_3D) {
            fmod_mode_ = fmod_mode_ ^ FMOD_3D;
        }
    }
    FMOD_RESULT result = fmod_channel_->setMode(fmod_mode_);
    if (result != FMOD_OK) {
        LOG_ERROR("AudioSource::Set3DMode FMOD_Channel_SetMode result:{}", (int)result);
    }
}

void AudioSource::Play() {
    if (audio_clip_ == nullptr) {
        LOG_ERROR("AudioSource::Play audio_clip_== nullptr");
        return;
    }
    if (audio_clip_->fmod_sound() == nullptr) {
        LOG_ERROR("AudioSource::Play audio_clip_->fmod_sound()==nullptr");
        return;
    }
    FMOD_RESULT result;
    bool paused = false;
    //判断音效是否暂停
    result = fmod_channel_->getPaused(&paused); //音效播放完毕后，channel被回收，返回 FMOD_ERR_INVALID_HANDLE
    switch (result) {
    case FMOD_OK:
        if (paused) {
            result = fmod_channel_->setPaused(false);
        }
        break;
    case FMOD_ERR_INVALID_PARAM://channel默认是nullptr，非法参数。
    case FMOD_ERR_INVALID_HANDLE://音效播放完毕后，channel被回收。
    case FMOD_ERR_CHANNEL_STOLEN://音效播放完毕后，channel被回收且被分配给其他Sound。
        //播放音效
        result = AudioCore::PlaySound(audio_clip_->fmod_sound(), nullptr, false, &fmod_channel_);
        break;
    default:
        break;
    }
}

void AudioSource::Pause() {
    FMOD_RESULT result;
    bool paused = false;
    //判断音效是否暂停
    result = fmod_channel_->getPaused(&paused);//音效播放完毕后，channel被回收，返回 FMOD_ERR_INVALID_HANDLE
    if (result == FMOD_OK) {
        if (!paused) {
            result = fmod_channel_->setPaused(true);//暂停播放
        }
        return;
    }
    LOG_ERROR("AudioSource::Paused FMOD_Channel_GetPaused result:{}", (int)result);
}

void AudioSource::Stop() {
    FMOD_RESULT result;
    result = fmod_channel_->stop();
    if (result == FMOD_OK) {
        return;
    }
    LOG_ERROR("AudioSource::Stop FMOD_Channel_Stop result:{}", (int)result);
}

bool AudioSource::Paused() {
    FMOD_RESULT result;
    bool paused = false;
    //判断音效是否暂停
    result = fmod_channel_->getPaused(&paused);//音效播放完毕后，channel被回收，返回 FMOD_ERR_INVALID_HANDLE
    if (result == FMOD_OK) {
        return paused;
    }
    LOG_ERROR("AudioSource::Paused FMOD_Channel_GetPaused result:{}", (int)result);
    return true;
}

void AudioSource::SetLoop(bool mode_loop) {
    if (mode_loop) {
        fmod_mode_ = fmod_mode_ | FMOD_LOOP_NORMAL;
    }
    else {
        if (fmod_mode_ & FMOD_LOOP_NORMAL) {
            fmod_mode_ = fmod_mode_ ^ FMOD_LOOP_NORMAL;
        }
    }

    FMOD_RESULT result = fmod_channel_->setMode(fmod_mode_);
    if (result != FMOD_OK) {
        LOG_ERROR("AudioSource::SetLoop FMOD_Channel_SetMode result:{}", (int)result);
    }
}

void AudioSource::Update() {
    Component::Update();

    if (fmod_mode_ ^ FMOD_3D) {
        auto transform = game_object()->GetComponent<Transform>();
        if (!transform) {
            return;
        }
        auto pos = transform->m_position;
        FMOD_VECTOR audio_source_pos = { pos.x, pos.y, pos.z };
        FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
        fmod_channel_->set3DAttributes(&audio_source_pos, &vel);
    }
}
