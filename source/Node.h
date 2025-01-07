#pragma once

#include <vector>

class Node {
   public:
    enum NodeType { NODE,
                    NODE3D,
                    MESH3D,
                    CAMERA3D,
                    ANIMATOR,
                    TIMER };
    virtual NodeType GetType() const { return NODE; }
    Node();
    virtual ~Node();

    Node* GetParent();
    void SetParent(Node* _parent);

    void AddChild(Node* child);
    bool RemoveChild(Node* child);
    bool RemoveChild(size_t index);
    int ChildCount();
    Node* ChildAt(size_t index);
    const std::vector<Node*> GetChildren() const;

    virtual void Update();

   protected:
    std::vector<Node*> children;
    Node* parent;
};