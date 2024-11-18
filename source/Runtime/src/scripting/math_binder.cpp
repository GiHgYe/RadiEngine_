#include "scripting/math_binder.h"
#include "math/math_headers.h"
#include "serializer/all_serializer.h"

void LuaMathBinder::binding(sol::state& sol_state_)
{
	// bind Vector2
	{
		auto math_table = sol_state_["Math"].get_or_create<sol::table>();
		math_table.new_usertype<Vector2>("Vector2", sol::call_constructor,
			sol::constructors < Vector2(), Vector2(float), Vector2(float, float)>(),
			"x", &Vector2::x, "y", &Vector2::y
		);
	}

	// bind Quaternion
	{
		auto math_table = sol_state_["Math"].get_or_create<sol::table>();
		math_table.new_usertype<Quaternion>("Quaternion", sol::call_constructor, sol::constructors<Quaternion(), Quaternion(float, float, float, float)>(),
			"w", &Quaternion::w, "x", &Quaternion::x, "y", &Quaternion::y, "z", &Quaternion::z,
			sol::meta_function::multiplication, sol::overload(
				[](const Quaternion& lhs, const Quaternion& rhs) { return lhs * rhs; },
				[](const Quaternion& lhs, float rhs) { return lhs * rhs; },
				[](float lhs, const Quaternion& rhs) { return lhs * rhs; },
				[](const Quaternion& lhs, const Vector3& rhs) { return lhs * rhs; }
			),
			sol::meta_function::addition, [](const Quaternion& lhs, const Quaternion& rhs) { return lhs + rhs; },
			sol::meta_function::subtraction, [](const Quaternion& lhs, const Quaternion& rhs) { return lhs - rhs; },
			sol::meta_function::division, [](const Quaternion& lhs, float rhs) { return lhs / rhs; },
			sol::meta_function::unary_minus, [](const Quaternion& q) { return -q; },
			sol::meta_function::equal_to, [](const Quaternion& lhs, const Quaternion& rhs) { return lhs == rhs; },
			"GetQuaternionFromAngleAxis", &Quaternion::GetQuaternionFromAngleAxis
		);
	}

	// bind Math Function
	{
		auto math_table = sol_state_["Math"].get_or_create<sol::table>();
		math_table.set("Pi", Math_PI);
		math_table.set_function("Abs", &Math::Abs);
		math_table.set_function("IsNan", &Math::IsNan);
		math_table.set_function("Sqr", &Math::Sqr);
		math_table.set_function("Sqrt", &Math::Sqrt);
		math_table.set_function("InvSqrt", &Math::InvSqrt);
		math_table.set_function("RealEqual", &Math::RealEqual);
		math_table.set_function("Clamp", &Math::Clamp);
		math_table.set_function("GetMaxElement", &Math::GetMaxElement);
		math_table.set_function("DegreesToRadians", &Math::DegreesToRadians);
		math_table.set_function("RadiansToDegrees", &Math::RadiansToDegrees);
		math_table.set_function("AngleUnitsToRadians", &Math::AngleUnitsToRadians);
		math_table.set_function("RadiansToAngleUnits", &Math::RadiansToAngleUnits);
		math_table.set_function("AngleUnitsToDegrees", &Math::AngleUnitsToDegrees);
		math_table.set_function("DegreesToAngleUnits", &Math::DegreesToAngleUnits);
		math_table.set_function("Sin", (float(*)(float)) & Math::Sin);
		math_table.set_function("Cos", (float(*)(float)) & Math::Cos);
		math_table.set_function("Tan", (float(*)(float)) & Math::Tan);
		math_table.set_function("Acos", &Math::Acos);
		math_table.set_function("Asin", &Math::Asin);
		math_table.set_function("Atan", &Math::Atan);
		math_table.set_function("Atan2", &Math::Atan2);
	}

	// bind Radian
	{
		auto math_table = sol_state_["Math"].get_or_create<sol::table>();
		math_table.new_usertype<Radian>(
			"Radian", sol::call_constructor,
			sol::constructors<Radian(float), Radian(const Degree&)>(),
			"ValueRadians", &Radian::ValueRadians,
			"ValueDegrees", &Radian::ValueDegrees,
			"ValueAngleUnits", &Radian::ValueAngleUnits,
			"SetValue", &Radian::SetValue
		);
	}

	// bind Degree
	{
		auto math_table = sol_state_["Math"].get_or_create<sol::table>();
		math_table.new_usertype<Degree>(
			"Degree", sol::call_constructor,
			sol::constructors<Degree(float), Degree(const Radian&)>(),
			"ValueDegrees", &Degree::ValueDegrees,
			"ValueRadians", &Degree::ValueRadians,
			"ValueAngleUnits", &Degree::ValueAngleUnits
		);
	}

	// bind Angle
	{
		auto math_table = sol_state_["Math"].get_or_create<sol::table>();
		math_table.new_usertype<Angle>("Angle", sol::call_constructor, sol::constructors<Angle(), Angle(float)>(),
			"Degree", &Angle::operator Degree,
			"Radian", &Angle::operator Radian
		);
	}

	// bind Vector3
	{
		auto math_table = sol_state_["Math"].get_or_create<sol::table>();
		math_table.new_usertype<Vector3>(
			"Vector3", sol::call_constructor,
			sol::constructors<Vector3(), Vector3(float), Vector3(float, float, float), Vector3(Vector4)>(),
			"x", &Vector3::x,
			"y", &Vector3::y,
			"z", &Vector3::z,
			sol::meta_function::addition, sol::overload(
				[](const Vector3& lhs, const Vector3& rhs) { return lhs + rhs; },
				[](float lhs, const Vector3& rhs) { return lhs + rhs; },
				[](const Vector3& lhs, float rhs) { return lhs + rhs; }
			),
			sol::meta_function::subtraction, sol::overload(
				[](const Vector3& lhs, const Vector3& rhs) { return lhs - rhs; },
				[](float lhs, const Vector3& rhs) { return lhs - rhs; },
				[](const Vector3& lhs, float rhs) { return lhs - rhs; }
			),
			sol::meta_function::multiplication, sol::overload(
				[](const Vector3& lhs, const Vector3& rhs) { return lhs * rhs; },
				[](float lhs, const Vector3& rhs) { return lhs * rhs; },
				[](const Vector3& lhs, float rhs) { return lhs * rhs; }
			),
			sol::meta_function::division, sol::overload(
				[](const Vector3& lhs, const Vector3& rhs) { return lhs / rhs; },
				[](float lhs, const Vector3& rhs) { return lhs / rhs; },
				[](const Vector3& lhs, float rhs) { return lhs / rhs; }
			),
			sol::meta_function::equal_to, [](const Vector3& lhs, const Vector3& rhs) { return lhs == rhs; },
			sol::meta_function::unary_minus, [](const Vector3& v) { return -v; },
			sol::meta_function::to_string, [](const Vector3& v) { return Serializer::Write(v).dump(); },
			"Length", &Vector3::Length,
			"SquaredLength", &Vector3::SquaredLength,
			"AbsoluteCopy", &Vector3::AbsoluteCopy,
			"AngleBetween", &Vector3::AngleBetween,
			"Cross", &Vector3::CrossProduct,
			"Dot", &Vector3::DotProduct,
			"Distance", &Vector3::Distance,
			"SquaredDistance", &Vector3::SquaredDistance,
			"Normalise", &Vector3::Normalise,
			"NormalisedCopy", &Vector3::NormalisedCopy,
			"MakeFloor", &Vector3::MakeFloor,
			"MakeCeil", &Vector3::MakeCeil,
			"IsZeroLength", &Vector3::IsZeroLength,
			"IsZero", &Vector3::IsZero,
			"Reflect", &Vector3::Reflect,
			"Project", &Vector3::Project,
			"Clamp", &Vector3::Clamp,
			"Lerp", &Vector3::Lerp,
			"GetMaxElement", &Vector3::GetMaxElement,
			"IsNaN", &Vector3::IsNaN
		);
	}

	// bind Vector4
	{
		auto math_table = sol_state_["Math"].get_or_create<sol::table>();
		math_table.new_usertype<Vector4>(
			"Vector4", sol::call_constructor,
			sol::constructors<Vector4(), Vector4(float, float, float, float), Vector4(Vector3, float)>(),
			"x", &Vector4::x,
			"y", &Vector4::y,
			"z", &Vector4::z,
			"w", &Vector4::w,
			sol::meta_function::addition, sol::overload(
				[](const Vector4& lhs, const Vector4& rhs) { return lhs + rhs; },
				[](float lhs, const Vector4& rhs) { return lhs + rhs; },
				[](const Vector4& lhs, float rhs) { return lhs + rhs; }
			),
			sol::meta_function::subtraction, sol::overload(
				[](const Vector4& lhs, const Vector4& rhs) { return lhs - rhs; },
				[](float lhs, const Vector4& rhs) { return lhs - rhs; },
				[](const Vector4& lhs, float rhs) { return lhs - rhs; }
			),
			sol::meta_function::multiplication, sol::overload(
				[](const Vector4& lhs, const Vector4& rhs) { return lhs * rhs; },
				[](float lhs, const Vector4& rhs) { return lhs * rhs; },
				[](const Vector4& lhs, float rhs) { return lhs * rhs; }
			),
			sol::meta_function::division, sol::overload(
				[](const Vector4& lhs, const Vector4& rhs) { return lhs / rhs; },
				[](float lhs, const Vector4& rhs) { return lhs / rhs; },
				[](const Vector4& lhs, float rhs) { return lhs / rhs; }
			),
			sol::meta_function::equal_to, [](const Vector4& lhs, const Vector4& rhs) { return lhs == rhs; },
			sol::meta_function::unary_minus, [](const Vector4& v) { return -v; },
			sol::meta_function::to_string, [](const Vector4& v) { return Serializer::Write(v).dump(); },
			"DotProduct", &Vector4::DotProduct,
			"IsNaN", &Vector4::IsNaN
		);
	}

	// Matrix4x4
	{
		auto math_table = sol_state_["Math"].get_or_create<sol::table>();
		math_table.new_usertype<Matrix4x4>
			(
				"Matrix4", sol::call_constructor,
				sol::constructors<Matrix4x4(), Matrix4x4(Vector4, Vector4, Vector4, Vector4)>(),
				sol::meta_function::addition, sol::overload([](const Matrix4x4& lhs, const Matrix4x4& rhs) { return lhs + rhs; }),
				sol::meta_function::subtraction, sol::overload([](const Matrix4x4& lhs, const Matrix4x4& rhs) { return lhs - rhs; }),
				sol::meta_function::multiplication, sol::overload(
					[](const Matrix4x4& lhs, const Matrix4x4& rhs) { return lhs * rhs; },
					[](const Matrix4x4& lhs, Vector4 rhs) { return lhs * rhs; },
					[](const Matrix4x4& lhs, Vector3 rhs) { return lhs * rhs; },
					[](const Matrix4x4& lhs, float rhs) { return lhs * rhs; }
				),
				sol::meta_function::unary_minus, [](const Matrix4x4& m) { return m * -1; },
				sol::meta_function::equal_to, [](const Matrix4x4& lhs, const Matrix4x4& rhs) { return lhs == rhs; },
				sol::meta_function::to_string, [](const Matrix4x4& mat) { return Serializer::Write(mat.ToMatrix4x4_()).dump(); },
				"MakeTransform", &Matrix4x4::MakeTransform,
				"MakeInverseTransform", &Matrix4x4::MakeInverseTransform,
				"Inverse", &Matrix4x4::Inverse
			);
	}

}
