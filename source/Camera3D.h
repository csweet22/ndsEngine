#pragma once

#include "Node3D.h"

class Camera3D : public Node3D {
   public:
    NodeType GetType() const override { return CAMERA3D; }
    Camera3D();
    ~Camera3D();
    virtual void Update();
    void UpdateLoadMVP();
    float zNear, zFar, fovY, aspect;
};