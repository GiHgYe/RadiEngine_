#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <meta/reflection/reflection.h>
#include "data_structs/tree.h"


class Component;
class GameObject : public Tree::Node
{
public:
    GameObject(const std::string& name);
    ~GameObject();

    std::string& name() { return name_; }
    void set_name(std::string name) { name_ = name; }

    unsigned char layer() { return layer_; }
    void set_layer(unsigned char layer) { layer_ = layer; }

    bool active() { return active_; }
    void set_active(bool active) { active_ = active; }

    /// 设置父节点
    /// \param parent
    /// \return
    bool SetParent(GameObject* parent);

public:
    /// 添加组件
    /// \tparam TComponent 组件类型
    /// \return TComponent* 组件实例
    template <class TComponent = Component>
    TComponent* AddComponent() {
        TComponent* component = new TComponent;
        AttachComponent(component);
        component->Awake();
        return static_cast<TComponent*>(component);
    }

    /// 附加组件实例
    void AttachComponent(Component* component);

    /// 获取组件
    /// \tparam TComponent 组件类型
    /// \return TComponent*  组件实例
    template<class TComponent = Component>
    TComponent* GetComponent() {
        std::string component_type_name = TComponent::ClassName();
        if (component_map_.find(component_type_name) == component_map_.end())
		    return nullptr;
	    if (component_map_[component_type_name].size() == 0)
		    return nullptr;
	    return static_cast<TComponent*>(component_map_[component_type_name][0]);
    }

    /// 获取所有同名组件
    /// \param component_type_name 组件类名
    /// \return
    std::vector<Component*>& GetComponents(const std::string& component_type_name);

    /// 遍历所有Component
    /// \param func
    void ForeachComponent(std::function<void(Component* component)> func);

private:
    std::string name_;
    std::unordered_map<std::string, std::vector<Component*>> component_map_;

    unsigned char layer_;   //将物体分不同的层，用于相机分层、物理碰撞分层等
    bool active_ = true;//是否激活

public:
    /// 遍历所有GameObject
    /// \param func
    static void Foreach(std::function<void(GameObject* game_object)> func);

    /// 全局查找GameObject
    /// \param name
    /// \return
    static GameObject* Find(std::string name);

private:
    static Tree game_object_tree_;    //存储所有的GameObject
};