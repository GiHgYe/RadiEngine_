#pragma once
#include "..\Runtime\include\renderer\camera.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const Camera& instance);
template<>
Camera& Serializer::Read(const Json& json_context, Camera& instance);


