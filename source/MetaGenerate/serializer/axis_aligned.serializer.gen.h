#pragma once
#include "..\Runtime\include\math\axis_aligned.h"


template<>
Json Serializer::Write(const AxisAlignedBox& instance);
template<>
AxisAlignedBox& Serializer::Read(const Json& json_context, AxisAlignedBox& instance);


