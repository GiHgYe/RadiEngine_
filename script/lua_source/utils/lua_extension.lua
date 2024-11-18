
function clone(object)
    local lookup_table = {}
    local function __copy(object)
        if type(object) ~= "table" then
            return object
        elseif lookup_table[object] then
            return lookup_table[object]
        end
        local new_table = {}
        lookup_table[object] = new_table
        for key, value in pairs(object) do
            new_table[__copy(key)] = __copy(value)
        end
        return setmetatable(new_table, getmetatable(object))
    end
    return __copy(object)
end


function Class(class_name, super)
    local super_type = type(super)
    local class
    if super_type ~= "table" then
        super = nil
    end
    if super ~= nil then
        class = clone(super)
        class.super = super
    else
        class = {ctor = function(...) end}
    end
    class.__cname = class_name
    class.__index = class

    function class.new(...)
        local instance = setmetatable({}, class)
        instance.class = class
        instance:ctor(...)
        return instance
    end

    function class.new_with(...)
        local instance = setmetatable({}, class)
        instance.class = class
        instance:ctor_with(...)
        return instance
    end

    return class
end

--- 判断继承关系
function IsSubClass(sub, super)
    if sub.__index == nil or sub.__index.super == nil then
        return false
    end
    if sub.__index.super == super then
        return true
    else
        return IsSubClass(sub.__index.super, super)
    end
end

--- 合并列表
function CombineList(t1, t2)
    for _, v in pairs(t2) do
        table.insert(t1, v)
    end
end

--- 打印table内容
function Table_Tostring(t)
    if t == nil then
        return "nil"
    end
    local tmpData = {}
    for k, v in pairs(t) do
        table.insert(tmpData, string.format("%s=%s[%s]", k, tostring(v), type(v)))
    end
    return string.format("{%s}", table.concat(tmpData, ', '))
end

--- 替换字符
function string_replace(src,find,new)
    find=string.gsub(find,"[%(%)%.%%%+%-%*%?%[%]%^%$]", function(c) return "%" .. c end)
    return string.gsub(src,find,new)
end

--- 判断字符串以 xx 开头
--- @param str string 需要判断的字符串
--- @param start_str string xx
function string_startswith(str,start_str)
    return string.sub(str,1,string.len(start_str))==start_str
end

--- 判断字符串以 xx 结尾
function string_endswith(str,end_str)
    return end_str=='' or string.sub(str,-string.len(end_str))==end_str
end
