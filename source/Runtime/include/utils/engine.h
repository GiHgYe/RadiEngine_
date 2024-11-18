#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine
{
public:
    static const std::string& data_path() { return data_path_; }
    static void set_data_path(std::string data_path) { data_path_ = data_path; }

    /// ��ʼ��
    static void Init();

    static void Run();

    static void UpdateScreenSize();

    /// ÿһ֡���߼����롣
    static void LogicTick();

    /// �߼�����ִ�к�Ӧ�õ���Ⱦ��
    static void RenderTick();

    static void ShutDown();

private:
    static std::string data_path_;

    static GLFWwindow* glfw_window_;
};