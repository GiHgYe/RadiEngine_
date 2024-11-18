#pragma once
#include "..\Runtime\include\audio\core\audio_listener.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const AudioListener& instance);
template<>
AudioListener& Serializer::Read(const Json& json_context, AudioListener& instance);


