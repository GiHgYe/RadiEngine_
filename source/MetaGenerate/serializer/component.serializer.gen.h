#pragma once
#include "..\Runtime\include\component\component.h"


template<>
Json Serializer::Write(const Component& instance);
template<>
Component& Serializer::Read(const Json& json_context, Component& instance);


