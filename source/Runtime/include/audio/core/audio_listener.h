#pragma once
#include "component/component.h"
#include "audio/core/audio_core.h"

REFLECTION_TYPE(AudioListener)
CLASS(AudioListener : public Component, WhiteListFields)
{
	REFLECTION_BODY(AudioListener)
	REFLECTION_INFO(AudioListener)
public:
	AudioListener();

	virtual void Awake();
	virtual void Update();

private:
	unsigned int listener_id_ = 0;
	static unsigned int listener_num_;//已经创建的listener
};
