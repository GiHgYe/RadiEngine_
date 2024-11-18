#pragma once
#include "..\Runtime\include\math\quaternion.h"


template<>
Json Serializer::Write(const Quaternion& instance);
template<>
Quaternion& Serializer::Read(const Json& json_context, Quaternion& instance);


