#pragma once

#include "Node3D.h"
#include "MeshData.h"

class Mesh3D : public Node3D {
   public:
    NodeType GetType() const override { return MESH3D; }
    Mesh3D();
    ~Mesh3D();
    virtual void Update();
    virtual void Draw();
    MeshData* meshData;
};