#include "audio/core/audio_listener.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "utils/debug.h"


unsigned int AudioListener::listener_num_ = 0;

AudioListener::AudioListener() :Component() {
    listener_id_ = listener_num_++;
}

void AudioListener::Awake() {}

void AudioListener::Update() {
    Component::Update();
    auto transform = game_object()->GetComponent<Transform>();
    if (!transform) {
        return;
    }
    auto pos = transform->m_position;

    FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
    FMOD_VECTOR audio_listener_pos = { pos.x, pos.y, pos.z };
    FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };
    FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };
    AudioCore::Set3DListenerAttributes(listener_id_, &audio_listener_pos, &vel, &forward, &up);
}