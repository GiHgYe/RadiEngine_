#pragma once
#include <sol/sol.hpp>


class LuaRendererBinder {
public:
	static void binding(sol::state& sol_state_);
};