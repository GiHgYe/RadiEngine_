#pragma once

#include <fmod/core/fmod.hpp>
#include <fmod/studio/fmod_studio.hpp>

class AudioStudioEvent {
public:
    AudioStudioEvent();
    ~AudioStudioEvent();

    FMOD::Studio::EventInstance* event_instance(){return event_instance_;}
    void set_event_instance(FMOD::Studio::EventInstance* event_instance){event_instance_=event_instance;}

    /// 设置Event参数
    /// \param name
    /// \param value
    /// \param ignore_seek_speed
    /// \return
    FMOD_RESULT SetParameterByName(const char *name, float value, bool ignore_seek_speed = false);

    /// 设置Event 3D属性
    /// \param x
    /// \param y
    /// \param z
    /// \return
    FMOD_RESULT Set3DAttribute(float x,float y,float z);

    /// 播放Event实例
    void Start();

    void Stop();

    /// 暂停
    void Pause();
private:
    FMOD::Studio::EventInstance* event_instance_;
};

