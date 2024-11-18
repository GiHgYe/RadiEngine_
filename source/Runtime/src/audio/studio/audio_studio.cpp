#include "audio/studio/audio_studio.h"
#include "utils/debug.h"

FMOD::Studio::System* AudioStudio::system_;

FMOD_RESULT AudioStudio::Init() {
    FMOD_RESULT result = FMOD::Studio::System::create(&system_);
    if(result!=FMOD_OK){
        return result;
    }
    result = system_->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
    if(result!=FMOD_OK){
        return result;
    }
    return FMOD_OK;
}

FMOD_RESULT AudioStudio::Update() {
    if (system_== nullptr){
        return FMOD_ERR_INITIALIZATION;
    }
    return system_->update();
}

FMOD_RESULT AudioStudio::LoadBankFile(string file_name) {
    string bank_path = file_name;
    FMOD::Studio::Bank* bank= nullptr;
    return system_->loadBankFile(bank_path.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
}

AudioStudioEvent* AudioStudio::CreateEventInstance(const char *event_path) {
    FMOD::Studio::EventDescription* event_description= nullptr;
    FMOD_RESULT result = system_->getEvent(event_path, &event_description);
    if(result!=FMOD_OK){
        LOG_ERROR("FMOD_Studio_System_GetEvent result:{},event_path:{}", (int)result, event_path);
        return nullptr;
    }
    FMOD::Studio::EventInstance* event_instance=nullptr;
    result = event_description->createInstance(&event_instance);
    if(result!=FMOD_OK){
        LOG_ERROR("FMOD_Studio_EventDescription_CreateInstance result:{},event_path:{}",(int)result,event_path);
        return nullptr;
    }
    AudioStudioEvent* audio_studio_event=new AudioStudioEvent();
    audio_studio_event->set_event_instance(event_instance);
    return audio_studio_event;
}

void AudioStudio::setListenerAttributes(float x, float y, float z) {
    FMOD_3D_ATTRIBUTES attributes = { { x,y,z } };
    attributes.forward.z = 1.0f;
    attributes.up.y = 1.0f;
    system_->setListenerAttributes(0, &attributes, 0);
}




