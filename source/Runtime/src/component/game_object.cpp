#include "component/game_object.h"
#include "component/component.h"
#include "utils/debug.h"

Tree GameObject::game_object_tree_;

GameObject::GameObject(const std::string& name)
	: layer_(0x01)
{
	set_name(name);
	game_object_tree_.root_node()->AddChildren(this);
}

GameObject::~GameObject()
{
}

void GameObject::AttachComponent(Component* component)
{
	component->set_game_object(this);
	std::string component_type_name = component->get_name();
	if (component_map_.find(component_type_name) == component_map_.end()) {
		std::vector<Component*> component_vec;
		component_vec.push_back(component);
		component_map_[component_type_name] = component_vec;
	}
	else {
		component_map_[component_type_name].push_back(component);
	}
}

std::vector<Component*>& GameObject::GetComponents(const std::string& component_type_name) {
	return component_map_[component_type_name];
}

void GameObject::ForeachComponent(std::function<void(Component* component)> func)
{
	for (auto var : component_map_) {
		for (auto iter : var.second) {
			Component* component = iter;
			func(component);
		}
	}
}

bool GameObject::SetParent(GameObject* parent)
{
	if (parent == nullptr) {
		LOG_ERROR("parent null");
		return false;
	}
	parent->AddChildren(this);
	return true;
}

void GameObject::Foreach(std::function<void(GameObject* game_object)> func)
{
	game_object_tree_.Post(game_object_tree_.root_node(), [&func](Tree::Node* node) {
		auto n = node;
		GameObject* game_object = dynamic_cast<GameObject*>(n);
		func(game_object);
	});
}

GameObject* GameObject::Find(std::string name)
{
	GameObject* game_object_find = nullptr;
	game_object_tree_.Find(game_object_tree_.root_node(), [&name](Tree::Node* node) {
		GameObject* game_object = dynamic_cast<GameObject*>(node);
		if (game_object->name() == name)
			return true;
		return false;
	}, reinterpret_cast<Node**>(&game_object_find));
	return game_object_find;
}
