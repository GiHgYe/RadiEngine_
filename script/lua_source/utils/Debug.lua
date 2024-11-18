

Debug={}

function Debug:Init()
    --Cpp.Debug.Init()
end

--- 连接调试服务器
--- @param host string @服务器地址，默认是 127.0.0.1
--- @param port number @端口，默认是 8818
function Debug:ConnectDebugServer(host,port)
    if host==nil then
        host="127.0.0.1"
    end
    if port==nil then
        port=8818
    end
    require("LuaPanda").start(host,port);
end