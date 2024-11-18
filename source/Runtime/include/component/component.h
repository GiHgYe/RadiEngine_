#pragma once
#include "meta/reflection/reflection.h"
#include <sol/sol.hpp>

class GameObject;
REFLECTION_TYPE(Component)
CLASS (Component, WhiteListFields)
{
	REFLECTION_BODY(Component)
	REFLECTION_INFO(Component)
public:
	Component();
	virtual ~Component();

	GameObject* game_object() { return game_object_; }
	void set_game_object(GameObject* game_object) { game_object_ = game_object; }

	/// ���ö�Ӧ��Lua���
	/// \param lua_component_instance
	void set_lua_component_instance(sol::table lua_component_instance) {
		lua_component_instance_ = lua_component_instance;
	}

private:
	/// ͬ������Lua�������
	/// \param function_name
	void SyncLuaComponent(const char* function_name);

public:
	virtual void Awake();
	virtual void Update();

	/// ��Ⱦ֮ǰ
	virtual void OnPreRender();
	/// ��Ⱦ֮��
	virtual void OnPostRender();

	virtual void OnEnable();
	virtual void OnDisable();
private:
	GameObject* game_object_ = nullptr;
	sol::table lua_component_instance_;
};
