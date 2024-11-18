#pragma once
#include "math/matrix4.h"
#include "component/component.h"

REFLECTION_TYPE(Transform)
CLASS(Transform : public Component, Fields) 
{
	REFLECTION_BODY(Transform);
	REFLECTION_INFO(Transform)
public:
	Vector3    m_position{ Vector3::ZERO };
	Vector3    m_scale{ Vector3::UNIT_SCALE };
	Quaternion m_rotation{ Quaternion::IDENTITY };

	Transform() = default;
	Transform(const Vector3 & position, const Quaternion & rotation, const Vector3 & scale) :
		m_position{ position }, m_scale{ scale }, m_rotation{ rotation }
	{}


	Matrix4x4 GetMatrix() const
	{
		Matrix4x4 temp;
		temp.MakeTransform(m_position, m_scale, m_rotation);
		return temp;
	}

};


 // WhiteListFields