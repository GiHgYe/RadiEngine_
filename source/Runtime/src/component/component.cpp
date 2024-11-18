#include "component/component.h"
#include "utils/debug.h"
#include <meta/serializer/serializer.h>

Component::Component() {}

Component::~Component() {}

void Component::SyncLuaComponent(const char* function_name) {
	if (!lua_component_instance_.valid()) return;
	sol::protected_function function_awake = lua_component_instance_[function_name];
	if (!function_awake.valid()) return;
	auto result = function_awake(lua_component_instance_);
	if (result.valid() == false) {
		sol::error error = result;
		std::string name = lua_component_instance_["__cname"];
		LOG_ERROR("\n----RUN LUA_FUNCTION ERROR----\nComponent call Awake error,type:{}\n {}\n------------------------", name, error.what());
	}
}

void Component::Awake() {
	SyncLuaComponent("Awake");
}

void Component::Update() {
	SyncLuaComponent("Update");
}

void Component::OnPreRender() {
	SyncLuaComponent("OnPreRender");
}

void Component::OnPostRender() {
	SyncLuaComponent("OnPostRender");
}

void Component::OnEnable() {
	SyncLuaComponent("OnEnable");
}

void Component::OnDisable() {
	SyncLuaComponent("OnDisable");
}