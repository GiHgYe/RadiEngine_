#include "scripting/lua_binder.h"
extern "C" {
#include <lua_socket/luasocket.h>
}
#include "utils/debug.h"
#include "scripting/component_binder.h"
#include "scripting/renderer_binder.h"
#include "scripting/global_binder.h"
#include "scripting/math_binder.h"


sol::state LuaBinder::sol_state_;

void LuaBinder::Init(std::vector<std::string> package_paths)
{
	sol_state_.open_libraries();
	sol_state_.require("socket.core", luaopen_socket_core, true);
	// Set package path
	sol::table package_table = sol_state_["package"];
	std::string path = package_table["path"];
	path.append(";");
	for (auto& package_path : package_paths) {
		path.append(package_path);
		path.append(";");
	}
	package_table["path"] = path;
}

void LuaBinder::BindLua()
{
	LuaMathBinder::binding(sol_state_);
	LuaComponentBinder::binding(sol_state_);
	LuaRendererBinder::binding(sol_state_);
	LuaGlobalBinder::binding(sol_state_);
}

void LuaBinder::RunLuaFile(std::string script_file_path)
{
	auto result = sol_state_.script_file(script_file_path);
	if (result.valid() == false) {
		sol::error err = result;
		LOG_ERROR("\n---- LOAD LUA ERROR ----\n{}\n------------------------", err.what());
	}
}

sol::protected_function_result LuaBinder::CallLuaFunction(std::string function_name)
{
	sol::protected_function main_function = sol_state_["main"];
	sol::protected_function_result result = main_function();
	if (result.valid() == false) {
		sol::error err = result;
		LOG_ERROR("\n---- RUN LUA_FUNCTION ERROR ----\n{}\n------------------------", err.what());
	}
	return result;
}
