#pragma once
#include <sol/sol.hpp>


class LuaGlobalBinder {
public:
	static void binding(sol::state& sol_state_);
};