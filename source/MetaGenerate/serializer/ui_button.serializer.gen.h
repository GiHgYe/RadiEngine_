#pragma once
#include "..\Runtime\include\ui\ui_button.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const UIButton& instance);
template<>
UIButton& Serializer::Read(const Json& json_context, UIButton& instance);


