-- require("lua_source.cpp_class")

-- ---@class Vector3 : CppClass
-- ---@field public new function
-- ---@field public new_with function
-- ---@field super table
-- Vector3 = Class("Vector3", CppClass)

-- --Vector3 构造器
-- function Vector3:ctor(...)
--     self.super.ctor(self, ...)
-- end

-- --Vector3 构造器
-- function Vector3:ctor_with(cpp_class_instance, ...)
--     self.cpp_class_instance = cpp_class_instance
-- end

-- function Vector3:InitCppClass(...)
--     self.cpp_class_instance = Cpp.Vector3.new(...)
-- end

-- --输出字符串
-- function Vector3:__tostring()
--     return self.cpp_class_instance:__tostring()
-- end

-- --Add
-- function Vector3.__add(lhs, rhs)
--     if type(lhs) ~= "table" then
--         return Vector3.new_with(lhs + rhs.cpp_class_instance)
--     elseif type(rhs) ~= "table" then
--         return Vector3.new_with(lhs.cpp_class_instance + rhs)
--     else
--         return Vector3.new_with(lhs.cpp_class_instance + rhs.cpp_class_instance)
--     end
-- end

-- function Vector3.__sub(lhs, rhs)
--     if type(lhs) ~= "table" then
--         return Vector3.new_with(lhs - rhs.cpp_class_instance)
--     elseif type(rhs) ~= "table" then
--         return Vector3.new_with(lhs.cpp_class_instance - rhs)
--     else
--         return Vector3.new_with(lhs.cpp_class_instance - rhs.cpp_class_instance)
--     end
-- end

-- function Vector3.__mul(lhs, rhs)
--     if type(lhs) ~= "table" then
--         return Vector3.new_with(lhs * rhs.cpp_class_instance)
--     elseif type(rhs) ~= "table" then
--         return Vector3.new_with(lhs.cpp_class_instance * rhs)
--     else
--         return Vector3.new_with(lhs.cpp_class_instance * rhs.cpp_class_instance)
--     end
-- end

-- function Vector3.__div(lhs, rhs)
--     if type(lhs) ~= "table" then
--         return Vector3.new_with(lhs / rhs.cpp_class_instance)
--     elseif type(rhs) ~= "table" then
--         return Vector3.new_with(lhs.cpp_class_instance / rhs)
--     else
--         return Vector3.new_with(lhs.cpp_class_instance / rhs.cpp_class_instance)
--     end
-- end

-- ---@return Vector3
-- function Vector3:__unm()
--     return Vector3.new_with(self.cpp_class_instance:__unm())
-- end

-- function Vector3:__eq(v)
--     return self.cpp_class_instance == v.cpp_class_instance
-- end

-- ---返回向量长度
-- ---@return number
-- function Vector3:Length()
--     return self.cpp_class_instance:Length()
-- end

-- ---返回向量平方长度
-- ---@return number
-- function Vector3:SquaredLength()
--     return self.cpp_class_instance:SquaredLength()
-- end

-- ---返回绝对值向量
-- ---@return Vector3
-- function Vector3:AbsoluteCopy()
--     return Vector3.new_with(self.cpp_class_instance:AbsoluteCopy())
-- end

-- -- ---返回从当前向量旋转到dest向量的弧度
-- -- ---@return Radian
-- -- function Vector3:AngleBetween(dest)
-- --     return self.cpp_class_instance:AngleBetween(dest)
-- -- end

-- ---向量叉积
-- ---@return Vector3
-- function Vector3:CrossProduct(v)
--     return Vector3.new_with(self.cpp_class_instance:CrossProduct(v.cpp_class_instance))
-- end

-- ---向量点乘
-- ---@return Vector3 
-- function Vector3:DotProduct(v)
--     return Vector3.new_with(self.cpp_class_instance:DotProduct(v.cpp_class_instance))
-- end

-- ---返回当前点到目标点的距离
-- ---@return number
-- function Vector3:Distance(dest)
--     return self.cpp_class_instance:Distance(dest)
-- end

-- ---返回当前点到目标点的平方距离
-- ---@return number
-- function Vector3:SquaredDistance()
--     return self.cpp_class_instance:SquaredDistance()
-- end

-- ---归一化向量
-- function Vector3:Normalise()
--     self.cpp_class_instance:Normalise()
-- end

-- ---返回归一化向量
-- ---@return Vector3 @归一化向量
-- function Vector3:NormalisedCopy()
--     return Vector3.new_with(self.cpp_class_instance:NormalisedCopy())
-- end

-- ---使向量小于等于cmp向量
-- ---@param cmp Vector3 比较向量
-- function Vector3:MakeFloor(cmp)
--     self.cpp_class_instance:MakeFloor(cmp.cpp_class_instance)
-- end

-- ---使向量大于等于cmp向量
-- ---@param cmp Vector3 比较向量
-- function Vector3:MakeCeil(cmp)
--     self.cpp_class_instance:MakeCeil(cmp.cpp_class_instance)
-- end

-- --- 判断向量长度是否为0
-- ---@return boolean
-- function Vector3:IsZeroLength()
--     return self.cpp_class_instance:IsZeroLength()
-- end

-- ---判断向量分量是否为0
-- ---@return boolean
-- function Vector3:IsZero()
--     return self.cpp_class_instance:IsZero()
-- end

-- ---获得反射向量
-- ---@param normal Vector3 法线
-- ---@return Vector3 @反射向量
-- function Vector3:Reflect(normal)
--     return Vector3.new_with(self.cpp_class_instance:Reflect(normal))
-- end

-- ---获得投影向量
-- ---@param normal Vector3 法线
-- ---@return Vector3 @投影向量
-- function Vector3:Project(normal)
--     return Vector3.new_with(self.cpp_class_instance:Project(normal))
-- end

-- ---将向量限定在min到max内
-- ---@param min Vector3
-- ---@param max Vector3
-- ---@return Vector3 @限定后的向量
-- function Vector3:Clamp(min, max)
--     return Vector3.new_with(
--         self.cpp_class_instance:Clamp(min.cpp_class_instance, max.cpp_class_instance))
-- end

-- ---根据alpha值在lhs到rhs间插值
-- ---@param lhs Vector3
-- ---@param rhs Vector3
-- ---@param alpha number
-- ---@return Vector3 @插值后的向量
-- function Vector3.Lerp(lhs, rhs, alpha)
--     return Vector3.new_with(
--         Cpp.Vector3.Lerp(lhs.cpp_class_instance, rhs.cpp_class_instance, alpha))
-- end

-- ---获取最大值
-- ---@return number @最大值
-- function Vector3:GetMaxElement()
--     return Cpp.Vector3.GetMaxElement(self)
-- end

-- ---判断是否为有效数值
-- ---@return boolean
-- function Vector3:IsNaN()
--     return self.cpp_class_instance:IsNaN()
-- end
