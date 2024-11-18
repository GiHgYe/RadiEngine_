#pragma once
#include "..\Runtime\include\renderer\animation.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const Animation& instance);
template<>
Animation& Serializer::Read(const Json& json_context, Animation& instance);


