#include "Node3D.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

Node3D::Node3D() {
}

Node3D::~Node3D() {
}

void Node3D::Update() {
    Node::Update();
}

glm::vec3 Node3D::GetLocalPosition() {
    return localPosition;
}

glm::vec3 Node3D::GetLocalRotation() {
    return localRotation;
}

glm::vec3 Node3D::GetLocalScale() {
    return localScale;
}

void Node3D::SetLocalPosition(glm::vec3 newPosition) {
    localPosition = newPosition;
}

void Node3D::SetLocalRotation(glm::vec3 newRotation) {
    localRotation = newRotation;

    glm::mat4 rotationMatrix = glm::mat4(1.0f);

    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(localRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(localRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(localRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Update the local directional vectors
    forward = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0, 0.0, -1.0, 0.0f)));
    up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0, -1.0, 0.0, 0.0f)));
    right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(1.0, 0.0, 0.0, 0.0f)));
}

void Node3D::SetLocalScale(glm::vec3 newScale) {
    localScale = newScale;
}

glm::vec3 Node3D::GetGlobalPosition() {
    // If I have a Node3D parent
    if (parent && (parent->GetType() == Node::NODE3D || parent->GetType() == Node::MESH3D || parent->GetType() == Node::CAMERA3D)) {
        Node3D* parent3D = static_cast<Node3D*>(parent);

        glm::vec3 parentGlobalPosition = parent3D->GetGlobalPosition();
        glm::vec3 parentGlobalRotation = parent3D->GetGlobalRotation();
        glm::vec3 parentGlobalScale = parent3D->GetGlobalScale();

        glm::vec3 worldPosition = localPosition;

        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(parentGlobalRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(parentGlobalRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(parentGlobalRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::vec3 rotatedPosition = glm::vec3(rotationMatrix * glm::vec4(worldPosition, 1.0f));

        rotatedPosition *= parentGlobalScale;

        worldPosition = parentGlobalPosition + rotatedPosition;

        return worldPosition;
    }

    return localPosition;
}

glm::vec3 Node3D::GetGlobalRotation() {
    // If I have a Node3D parent
    if (parent && (parent->GetType() == Node::NODE3D || parent->GetType() == Node::MESH3D || parent->GetType() == Node::CAMERA3D)) {
        Node3D* parent3D = static_cast<Node3D*>(parent);

        glm::vec3 parentGlobalRotation = parent3D->GetGlobalRotation();

        glm::vec3 globalRotation = localRotation + parentGlobalRotation;

        return globalRotation;
    }

    return localRotation;
}

glm::vec3 Node3D::GetGlobalScale() {
    // If I have a Node3D parent
    if (parent && (parent->GetType() == Node::NODE3D || parent->GetType() == Node::MESH3D || parent->GetType() == Node::CAMERA3D)) {
        Node3D* parent3D = static_cast<Node3D*>(parent);

        glm::vec3 parentGlobalScale = parent3D->GetGlobalScale();

        glm::vec3 globalScale = localScale * parentGlobalScale;

        return globalScale;
    }

    return localScale;
}

void Node3D::SetGlobalPosition(glm::vec3 newPosition) {
    // If I have a Node3D parent
    if (parent && (parent->GetType() == Node::NODE3D || parent->GetType() == Node::MESH3D || parent->GetType() == Node::CAMERA3D)) {
        Node3D* parent3D = static_cast<Node3D*>(parent);

        glm::vec3 parentGlobalPosition = parent3D->GetGlobalPosition();

        SetLocalPosition(newPosition - parentGlobalPosition);

    } else {
        SetLocalPosition(newPosition);
    }
}

void Node3D::SetGlobalRotation(glm::vec3 newRotation) {
    // If I have a Node3D parent
    if (parent && (parent->GetType() == Node::NODE3D || parent->GetType() == Node::MESH3D || parent->GetType() == Node::CAMERA3D)) {
        Node3D* parent3D = static_cast<Node3D*>(parent);

        glm::vec3 parentGlobalRotation = parent3D->GetGlobalRotation();

        SetLocalRotation(newRotation - parentGlobalRotation);
    } else {
        SetLocalRotation(newRotation);
    }
}

void Node3D::SetGlobalScale(glm::vec3 newScale) {
    // If I have a Node3D parent
    if (parent && (parent->GetType() == Node::NODE3D || parent->GetType() == Node::MESH3D || parent->GetType() == Node::CAMERA3D)) {
        Node3D* parent3D = static_cast<Node3D*>(parent);

        glm::vec3 parentGlobalScale = parent3D->GetGlobalScale();

        SetLocalScale(newScale / parentGlobalScale);
    } else {
        SetLocalScale(newScale);
    }
}

glm::vec3 Node3D::GetForward() {
    return forward;
}

glm::vec3 Node3D::GetUp() {
    return up;
}

glm::vec3 Node3D::GetRight() {
    return right;
}
