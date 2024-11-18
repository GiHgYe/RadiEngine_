#pragma once
#include "meta\reflection\reflection_register.h"
#include "meta\reflection\reflection.h"
#include "serializer\all_serializer.h"
#include "reflection\ui_mask.reflection.gen.h"
#include "reflection\component.reflection.gen.h"
#include "reflection\vector2.reflection.gen.h"
#include "reflection\audio_listener.reflection.gen.h"
#include "reflection\ui_text.reflection.gen.h"
#include "reflection\audio_source.reflection.gen.h"
#include "reflection\quaternion.reflection.gen.h"
#include "reflection\matrix4.reflection.gen.h"
#include "reflection\vector3.reflection.gen.h"
#include "reflection\vector4.reflection.gen.h"
#include "reflection\ui_button.reflection.gen.h"
#include "reflection\transform.reflection.gen.h"
#include "reflection\axis_aligned.reflection.gen.h"
#include "reflection\animation.reflection.gen.h"
#include "reflection\camera.reflection.gen.h"
#include "reflection\mesh_filter.reflection.gen.h"
#include "reflection\mesh_renderer.reflection.gen.h"
#include "reflection\ui_image.reflection.gen.h"
#include "reflection\ui_camera.reflection.gen.h"


namespace Reflection{
    void TypeMetaRegister::metaRegister(){
        TypeWrappersRegister::UiMask();
        TypeWrappersRegister::Component();
        TypeWrappersRegister::Vector2();
        TypeWrappersRegister::AudioListener();
        TypeWrappersRegister::UiText();
        TypeWrappersRegister::AudioSource();
        TypeWrappersRegister::Quaternion();
        TypeWrappersRegister::Matrix4();
        TypeWrappersRegister::Vector3();
        TypeWrappersRegister::Vector4();
        TypeWrappersRegister::UiButton();
        TypeWrappersRegister::Transform();
        TypeWrappersRegister::AxisAligned();
        TypeWrappersRegister::Animation();
        TypeWrappersRegister::Camera();
        TypeWrappersRegister::MeshFilter();
        TypeWrappersRegister::MeshRenderer();
        TypeWrappersRegister::UiImage();
        TypeWrappersRegister::UiCamera();
    }
}

