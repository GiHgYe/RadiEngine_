#pragma once
#include "..\Runtime\include\ui\ui_camera.h"
#include "serializer\camera.serializer.gen.h"


template<>
Json Serializer::Write(const UICamera& instance);
template<>
UICamera& Serializer::Read(const Json& json_context, UICamera& instance);


