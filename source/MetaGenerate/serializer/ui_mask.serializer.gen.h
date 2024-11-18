#pragma once
#include "..\Runtime\include\ui\ui_mask.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const UIMask& instance);
template<>
UIMask& Serializer::Read(const Json& json_context, UIMask& instance);


