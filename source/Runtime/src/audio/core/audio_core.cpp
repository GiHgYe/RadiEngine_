#include "audio/core/audio_core.h"
#include "utils/debug.h"

FMOD::System* AudioCore::fmod_system_;

void AudioCore::Init()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&fmod_system_);
	LOG_INFO("FMOD::System_Create ret code {}", (int)result);
	//获取版本号
	unsigned int      version;
	result = fmod_system_->getVersion(&version);
	LOG_INFO("FMOD_System_GetVersion ret code {}", (int)result);
	if (version < FMOD_VERSION) {
		LOG_ERROR("FMOD lib version {} doesn't match header version {}", version, FMOD_VERSION);
		return;
	}
	//初始化 系统
	result = fmod_system_->init(32, FMOD_INIT_NORMAL, 0);
	LOG_INFO("FMOD_System_Init ret code {}", (int)result);
}

FMOD_RESULT AudioCore::CreateSound(const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* ex_info, FMOD::Sound** sound)
{
	LOG_INFO("Audio::CreateSound name:{}", name_or_data);
	return fmod_system_->createSound(name_or_data, mode, ex_info, sound);
}

FMOD_RESULT AudioCore::PlaySound(FMOD::Sound* sound, FMOD::ChannelGroup* channel_group, bool paused, FMOD::Channel** channel)
{
	return fmod_system_->playSound(sound, channel_group, paused, channel);
}

FMOD_RESULT AudioCore::Update()
{
	if (fmod_system_ == nullptr) {
		return FMOD_ERR_UNINITIALIZED;
	}
	return fmod_system_->update();
}

FMOD_RESULT AudioCore::Set3DListenerAttributes(int listener, const FMOD_VECTOR* pos, const FMOD_VECTOR* vel, const FMOD_VECTOR* forward, const FMOD_VECTOR* up)
{
	return fmod_system_->set3DListenerAttributes(listener, pos, vel, forward, up);
}
