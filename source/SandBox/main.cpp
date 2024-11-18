#include <filesystem>
#define SOL_ALL_SAFETIES_ON 1
#include "scripting/lua_binder.h"

using namespace std;


int main()
{
    std::filesystem::path current_path = std::filesystem::current_path() / "script";

    LuaBinder::Init({
        (current_path/"?.lua").string(),
        (current_path/"lua"/"?.lua").string(),
        (current_path/"lua_source"/"?.lua").string()
    });


    LuaBinder::BindLua();

    LuaBinder::RunLuaFile((current_path/"main.lua").string());

    LuaBinder::CallLuaFunction("main");

    return 0;
}
