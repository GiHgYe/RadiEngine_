#pragma once
#include "..\Runtime\include\audio\core\audio_source.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const AudioSource& instance);
template<>
AudioSource& Serializer::Read(const Json& json_context, AudioSource& instance);


