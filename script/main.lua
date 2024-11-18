require("lua_source/utils/Debug")
require("utils/application")
require("component/game_object")
require("component/transform")
require("login_scene")

function main()
    Debug:ConnectDebugServer()

    Application:Init()--初始化引擎

    local go=GameObject.new("LoginSceneGo")
    go:AddComponent(LoginScene)

    Application:Run()--开始引擎主循环

    Application:ShutDown()--关闭引擎
end