#pragma once
#include "..\Runtime\include\renderer\skinned_mesh_renderer.h"
#include "serializer\mesh_renderer.serializer.gen.h"


template<>
Json Serializer::Write(const SkinnedMeshRenderer& instance);
template<>
SkinnedMeshRenderer& Serializer::Read(const Json& json_context, SkinnedMeshRenderer& instance);


