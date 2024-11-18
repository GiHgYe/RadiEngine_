require("utils/lua_extension")

--- @class CppClass c++ class 封装类
--- @field public cpp_class_instance table
CppClass = Class("CppClass")

--- 构造函数
function CppClass:ctor(...)
    self:InitCppClass(...)
end

--- 构造函数, 从已有的c++实例构造
--- @param cpp_class_instance table c++端实例
function CppClass:ctor_with(cpp_class_instance, ...)
    assert(cpp_class_instance, "ctor_with use an existing cpp instance")
    self.cpp_class_instance = cpp_class_instance
end

--- 初始化c++实例
function CppClass:InitCppClass(...)
    self.cpp_class_instance = nil
end

--- 获取c++实例
function CppClass:Cpp_Class_Instance()
    return self.cpp_class_instance
end

