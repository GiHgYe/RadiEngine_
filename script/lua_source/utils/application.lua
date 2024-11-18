

Application={

}

function Application:Init()
    Cpp.Engine.Init()
end

--- 开始引擎主循环
function Application:Run()
    Cpp.Engine.Run()
end

function Application:UpdateScreenSize()
    return Cpp.Engine.UpdateScreenSize()
end

function Application:ShutDown()
    Cpp.Engine.ShutDown()
end