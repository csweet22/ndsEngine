#include "Camera3D.h"

#include <nds.h>
#include <stdio.h>

Camera3D::Camera3D() {
    fovY = 70;
    aspect = 256.0 / 192.0;
    zNear = 0.1;
    zFar = 40;
    UpdateLoadMVP();
}

Camera3D::~Camera3D() {
}

void Camera3D::Update() {
    Node3D::Update();
}

void Camera3D::UpdateLoadMVP() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspectivef32(floattof32(fovY), floattof32(aspect), floattof32(zNear), floattof32(zFar));

    glm::vec3 globalPos = GetGlobalPosition();

    glm::vec3 viewTarget = globalPos + GetForward();

    gluLookAt(globalPos.x, globalPos.y, globalPos.z,     // camera possition
              viewTarget.x, viewTarget.y, viewTarget.z,  // look at
              GetUp().x, GetUp().y, GetUp().z);
}
