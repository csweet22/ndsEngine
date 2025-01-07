#pragma once

#include "../glm/glm.hpp"
#include "Node.h"

class Node3D : public Node {
   public:
    NodeType GetType() const override { return NODE3D; }
    Node3D();
    ~Node3D();

    virtual void Update();

    glm::vec3 GetLocalPosition();
    glm::vec3 GetLocalRotation();
    glm::vec3 GetLocalScale();
    void SetLocalPosition(glm::vec3 newPosition);
    void SetLocalRotation(glm::vec3 newRotation);
    void SetLocalScale(glm::vec3 newScale);

    glm::vec3 GetGlobalPosition();
    glm::vec3 GetGlobalRotation();
    glm::vec3 GetGlobalScale();
    void SetGlobalPosition(glm::vec3 newPosition);
    void SetGlobalRotation(glm::vec3 newRotation);
    void SetGlobalScale(glm::vec3 newScale);
    
    glm::vec3 GetForward();
    glm::vec3 GetUp();
    glm::vec3 GetRight();

   private:
    glm::vec3 localPosition = glm::vec3(0.0f);
    glm::vec3 localRotation = glm::vec3(0.0f);
    glm::vec3 localScale = glm::vec3(1.0f);

    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
};