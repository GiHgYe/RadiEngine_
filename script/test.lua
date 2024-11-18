package.path = package.path..";C:\\Users\\asus\\Desktop\\VSCodeFile\\?.lua;"

require("lua/socket")
require("LuaEnv/Test2")

local t = loadfile("Test2")

print(package.path)


