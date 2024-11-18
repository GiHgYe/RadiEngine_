#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine
{
public:
    static const std::string& data_path() { return data_path_; }
    static void set_data_path(std::string data_path) { data_path_ = data_path; }

    /// 初始化
    static void Init();

    static void Run();

    static void UpdateScreenSize();

    /// 每一帧内逻辑代码。
    static void LogicTick();

    /// 逻辑代码执行后，应用到渲染。
    static void RenderTick();

    static void ShutDown();

private:
    static std::string data_path_;

    static GLFWwindow* glfw_window_;
};