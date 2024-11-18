#pragma once
#include "..\Runtime\include\component\transform.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const Transform& instance);
template<>
Transform& Serializer::Read(const Json& json_context, Transform& instance);


