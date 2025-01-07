#include "Mesh3D.h"
#include "Renderer.h"

#include <nds.h>
#include <stdio.h>

Mesh3D::Mesh3D() {
}

Mesh3D::~Mesh3D() {
}

void Mesh3D::Update() {
    Node3D::Update();
    Draw();
}

void Mesh3D::Draw() {
    Renderer::GetInstance().Draw(this);
}
