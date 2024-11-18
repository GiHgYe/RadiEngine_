#pragma once

#include <list>
#include <functional>

class Tree
{
public:
	class Node {
	public:
		virtual ~Node() {}

		Node* parent() { return parent_; }
		void set_parent(Node* parent) { parent_ = parent; }

		std::list<Node*>& children() { return children_; }

		void AddChildren(Node* child) {
			if (child->parent() != nullptr) {
				child->parent()->RemoveChildren(child);
			}
			children_.push_back(child);
			child->set_parent(this);
		}

		void RemoveChildren(Node* child) { children_.remove(child); }
		
		bool Empty() { return children_.size() > 0; }
	private:
		Node* parent_ = nullptr;
		std::list<Node*> children_;
	};

public:
	Tree();
	~Tree();

	Node* root_node() { return root_node_; }

	void Post(Node* node, std::function<void(Node*)> func);

	void Find(Node* node_parent, std::function<bool(Node*)> function_check, Node** node_result);

private:
	Node* root_node_ = nullptr;
};