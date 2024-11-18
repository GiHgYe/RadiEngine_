#include "audio/audio.h"
#include "utils/debug.h"
#include "audio/core/audio_core.h"
#include "audio/studio/audio_studio.h"


void Audio::Init()
{
	AudioCore::Init();
}

void Audio::Update()
{
	AudioCore::Update();
}
