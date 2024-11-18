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

    /// ���ø��ڵ�
    /// \param parent
    /// \return
    bool SetParent(GameObject* parent);

public:
    /// ������
    /// \tparam TComponent �������
    /// \return TComponent* ���ʵ��
    template <class TComponent = Component>
    TComponent* AddComponent() {
        TComponent* component = new TComponent;
        AttachComponent(component);
        component->Awake();
        return static_cast<TComponent*>(component);
    }

    /// �������ʵ��
    void AttachComponent(Component* component);

    /// ��ȡ���
    /// \tparam TComponent �������
    /// \return TComponent*  ���ʵ��
    template<class TComponent = Component>
    TComponent* GetComponent() {
        std::string component_type_name = TComponent::ClassName();
        if (component_map_.find(component_type_name) == component_map_.end())
		    return nullptr;
	    if (component_map_[component_type_name].size() == 0)
		    return nullptr;
	    return static_cast<TComponent*>(component_map_[component_type_name][0]);
    }

    /// ��ȡ����ͬ�����
    /// \param component_type_name �������
    /// \return
    std::vector<Component*>& GetComponents(const std::string& component_type_name);

    /// ��������Component
    /// \param func
    void ForeachComponent(std::function<void(Component* component)> func);

private:
    std::string name_;
    std::unordered_map<std::string, std::vector<Component*>> component_map_;

    unsigned char layer_;   //������ֲ�ͬ�Ĳ㣬��������ֲ㡢������ײ�ֲ��
    bool active_ = true;//�Ƿ񼤻�

public:
    /// ��������GameObject
    /// \param func
    static void Foreach(std::function<void(GameObject* game_object)> func);

    /// ȫ�ֲ���GameObject
    /// \param name
    /// \return
    static GameObject* Find(std::string name);

private:
    static Tree game_object_tree_;    //�洢���е�GameObject
};