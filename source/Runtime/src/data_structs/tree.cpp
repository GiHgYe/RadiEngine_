#include "data_structs/tree.h"

Tree::Tree()
{
    root_node_ = new Node();
}

Tree::~Tree()
{
    //delete root_node_;
}

void Tree::Post(Node* node, std::function<void(Node*)> func)
{
    for (auto child : node->children()) {
        Post(child, func);
    }
    if (node != root_node_) {
        func(node);
    }
}

void Tree::Find(Node* node_parent, std::function<bool(Node*)> function_check, Node** node_result)
{
    for (auto child : node_parent->children()) {
        Find(child, function_check, node_result);
        if (*node_result != nullptr) {
            return;
        }
    }
    if (node_parent == root_node_) {
        return;
    }
    if (function_check(node_parent)) {
        (*node_result) = node_parent;
    }
}
