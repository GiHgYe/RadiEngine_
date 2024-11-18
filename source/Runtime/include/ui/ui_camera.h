#pragma once
#include "renderer/camera.h"

REFLECTION_TYPE(UICamera)
CLASS(UICamera : public Camera, WhiteListFields)
{
	REFLECTION_BODY(UICamera)
	REFLECTION_INFO(UICamera)
public:
    UICamera();
};