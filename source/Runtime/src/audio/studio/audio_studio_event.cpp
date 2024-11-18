#include "audio/studio/audio_studio_event.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "utils/debug.h"

AudioStudioEvent::AudioStudioEvent() {}
AudioStudioEvent::~AudioStudioEvent(){}


FMOD_RESULT AudioStudioEvent::SetParameterByName(const char *name, float value, bool ignore_seek_speed) {
    return event_instance_->setParameterByName(name, value, ignore_seek_speed);
}

FMOD_RESULT AudioStudioEvent::Set3DAttribute(float x,float y,float z){
    FMOD_3D_ATTRIBUTES attributes = { { x,y,z } };
    return event_instance_->set3DAttributes(&attributes);
}

void AudioStudioEvent::Start() {
    if(event_instance_== nullptr){
        LOG_ERROR("event_instance_== nullptr");
        return;
    }
    FMOD_RESULT result= event_instance_->start();
    if(result!=FMOD_OK){
        LOG_ERROR("FMOD_Studio_EventInstance_Start result:{}", (int)result);
        return;
    }
}

void AudioStudioEvent::Pause() {
    if(event_instance_== nullptr){
        LOG_ERROR("event_instance_== nullptr");
        return;
    }
    FMOD_RESULT result = event_instance_->setPaused(true);
    if(result!=FMOD_OK){
        LOG_ERROR("FMOD_Studio_EventInstance_SetPaused result:{}", (int)result);
        return;
    }
}

void AudioStudioEvent::Stop() {
    if(event_instance_== nullptr){
        LOG_ERROR("event_instance_== nullptr");
        return;
    }
    FMOD_RESULT result = event_instance_->stop(FMOD_STUDIO_STOP_MODE::FMOD_STUDIO_STOP_IMMEDIATE);
    if(result!=FMOD_OK){
        LOG_ERROR("FMOD_Studio_EventInstance_Stop result:{}", (int)result);
        return;
    }
}
