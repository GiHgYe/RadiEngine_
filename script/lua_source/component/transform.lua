
require("utils/lua_extension")

Transform=Class("Transform",Component)

function Transform:ctor()
    Transform.super.ctor(self)
end

function Transform:InitCppComponent()
    ---@type Cpp.Transform
    self.cpp_component_instance_=Cpp.Transform()
end


function Transform:position()
    return self.cpp_component_instance_.position
end

function Transform:rotation()
    return self.cpp_component_instance_.rotation
end

function Transform:scale()
    return self.cpp_component_instance_.scale
end

function Transform:set_position(position)
    self.cpp_component_instance_.position = position
end

function Transform:set_rotation(rotation)
    self.cpp_component_instance_.rotation = rotation
end

function Transform:set_scale(scale)
    self.cpp_component_instance_.scale = scale
end