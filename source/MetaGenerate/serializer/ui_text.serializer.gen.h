#pragma once
#include "..\Runtime\include\ui\ui_text.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const UIText& instance);
template<>
UIText& Serializer::Read(const Json& json_context, UIText& instance);


