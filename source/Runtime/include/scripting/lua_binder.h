#pragma once
#include <sol/sol.hpp>

class LuaBinder {
public:
    /// ��ʼ��
    /// \param package_path ����lua�ļ�����Ŀ¼
    static void Init(std::vector<std::string> package_paths);

    /// �����������ൽLua
    static void BindLua();

    /// ִ��Lua�ű��ļ�
    /// \param script_file_path
    static void RunLuaFile(std::string script_file_path);

    /// ����Lua����
    /// \param function_name
    /// \return
    static sol::protected_function_result CallLuaFunction(std::string function_name);

    static sol::state& sol_state() { return sol_state_; };

private:
    static sol::state sol_state_;
};