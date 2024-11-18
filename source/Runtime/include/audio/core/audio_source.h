#pragma once
#include "component/component.h"
#include "audio/core/audio_clip.h"


REFLECTION_TYPE(AudioSource)
CLASS(AudioSource : public Component, WhiteListFields)
{
	REFLECTION_BODY(AudioSource)
	REFLECTION_INFO(AudioSource)
public:
	AudioSource();

	AudioClip* audio_clip() { return audio_clip_; }
	void set_audio_clip(AudioClip * audio_clip) { audio_clip_ = audio_clip; }

	/// 设置为3D/2D音乐
	/// \param mode_3d
	void Set3DMode(bool mode_3d);

	/// 设置是否循环
	/// \param mode_loop
	void SetLoop(bool mode_loop);

	void Play();
	void Pause();
	void Stop();

	bool Paused();

private:
	void Update() override;

private:
	AudioClip* audio_clip_ = nullptr;
	FMOD::Channel* fmod_channel_ = nullptr;
	FMOD_MODE fmod_mode_ = FMOD_DEFAULT;
};