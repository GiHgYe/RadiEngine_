#include "utils/engine.h"
#ifdef WIN32
#include <Windows.h>
#endif
#include <stdexcept>
#include "utils/debug.h"
#include "utils/screen.h"
#include "utils/time.h"
#include "control/input.h"
#include "control/key_code.h"
#include "component/component.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "renderer/texture2d.h"
#include "renderer/mesh_filter.h"
#include "renderer/shader.h"
#include "renderer/material.h"
#include "renderer/mesh_renderer.h"
#include "renderer/camera.h"
#include "render_device/render_device_opengl.h"
#include "audio/audio.h"
#include <reflection/all_reflection.h>
#include <serializer/all_serializer.h>

std::string Engine::data_path_;
GLFWwindow* Engine::glfw_window_;


void Engine::Init()
{
    Reflection::TypeMetaRegister::metaRegister();
    RenderDevice::Init(new RenderDeviceOpenGL());
    //³õÊ¼»¯ fmod
    Audio::Init();
    Time::Init();
    glfwSetErrorCallback([](int error, const char* description) { fprintf(stderr, "GLFW Error %d: %s\n", error, description); });

    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW window");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfw_window_ = glfwCreateWindow(960, 640, "SandBox", NULL, NULL);
    if (!glfw_window_)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(glfw_window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    UpdateScreenSize();
    glfwSwapInterval(1);
    
    //glfwSetFramebufferSizeCallback(glfw_window_, [](GLFWwindow* windowint, int width, int height) { glViewport(0, 0, width, height); });
    glfwSetKeyCallback(glfw_window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) { Input::RecordKey(key, action); });
    glfwSetMouseButtonCallback(glfw_window_, [](GLFWwindow* window, int button, int action, int mods) { Input::RecordKey(button, action); });
    glfwSetScrollCallback(glfw_window_, [](GLFWwindow* window, double x, double y) { Input::RecordScroll(y); });
    glfwSetCursorPosCallback(glfw_window_, [](GLFWwindow* window, double x, double y) { Input::set_mousePosition(x, y); });
}

void Engine::LogicTick()
{
    UpdateScreenSize();

    GameObject::Foreach([](GameObject* game_object) {
        if (game_object->active()) {
            game_object->ForeachComponent([](Component* component) {
                component->Update();
            });
        }
    });

    Input::Update();
    Audio::Update();
    Time::Update();
}

void Engine::RenderTick()
{
    Camera::Foreach([&]() {
        GameObject::Foreach([](GameObject* game_object) {
            if (game_object->active() == false)
                return;
            auto mesh_renderer = game_object->GetComponent<MeshRenderer>();
            if (!mesh_renderer) return;
            mesh_renderer->Render();
        });
    });
}

void Engine::Run()
{
    while (!glfwWindowShouldClose(glfw_window_)) {

        LogicTick();
        RenderTick();

        glfwSwapBuffers(glfw_window_);
        glfwPollEvents();
    }
    glfwDestroyWindow(glfw_window_);
    glfwTerminate();
}

void Engine::UpdateScreenSize()
{
    int view_port_width, view_port_height;
    glfwGetFramebufferSize(glfw_window_, &view_port_width, &view_port_height);
    glViewport(0, 0, view_port_width, view_port_height);

    int window_width, window_height;
    glfwGetWindowSize(glfw_window_, &window_width, &window_height);
    Screen::set_width_height(window_width, window_height);
}


void Engine::ShutDown(){
    Reflection::TypeMetaRegister::metaUnregister();
}