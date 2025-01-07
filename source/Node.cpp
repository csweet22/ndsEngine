#include "Node.h"

#include <algorithm>

Node::Node() {
}

Node::~Node() {
    for (auto& child : GetChildren()) {
        delete child;
    }
}

Node* Node::GetParent() {
    return parent;
}

void Node::SetParent(Node* _parent) {
    parent = _parent;
}

void Node::AddChild(Node* child) {
    children.emplace_back(child);
    child->SetParent(this);
}

bool Node::RemoveChild(Node* child) {
    auto it = std::find(children.begin(), children.end(), child);

    if (it != children.end()) {
        children.erase(it);
        return true;
    }

    return false;
}

bool Node::RemoveChild(size_t index) {
    Node* child = ChildAt(index);
    if (child)
        return RemoveChild(child);
    return false;
}

int Node::ChildCount() {
    return children.size();
}

Node* Node::ChildAt(size_t index) {
    if (index < children.size())
        return children[index];

    return nullptr;
}

const std::vector<Node*> Node::GetChildren() const {
    return children;
}

void Node::Update() {
    for (auto& child : GetChildren()) {
        child->Update();
    }
}
