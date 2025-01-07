#pragma once

#include "Camera3D.h"
#include "Mesh3D.h"
#include "Singleton.h"

class Plane {
   public:
    glm::vec3 normal = {0.f, 1.f, 0.f};
    float distance = 0.f;

    Plane() {
    }
    Plane(glm::vec3 _normal, float _distance) {
        distance = _distance;
        normal = glm::normalize(_normal);
    }

    Plane(glm::vec3 _pointOnPlane, glm::vec3 _normal) {
        normal = glm::normalize(_normal);
        distance = glm::dot(normal, _pointOnPlane);
    }

    ~Plane() {
    }

    float getSignedDistanceToPlane(const glm::vec3& point) const {
        return glm::dot(normal, point) - distance;
    }
};

class Frustum {
   public:
    Frustum(Plane _topFace, Plane _bottomFace, Plane _rightFace,
            Plane _leftFace, Plane _farFace, Plane _nearFace)
        : topFace(_topFace), bottomFace(_bottomFace), rightFace(_rightFace), leftFace(_leftFace), farFace(_farFace), nearFace(_nearFace) {
    }
    Frustum(Camera3D* cam) {
        const float halfVSide = cam->zFar * tanf(cam->fovY * .5f);
        const float halfHSide = halfVSide * cam->aspect;
        const glm::vec3 frontMultFar = cam->zFar * cam->GetForward();

        nearFace = Plane(cam->GetGlobalPosition() + cam->zNear * cam->GetForward(), cam->GetForward());
        farFace = Plane(cam->GetGlobalPosition() + frontMultFar, -cam->GetForward());
        rightFace = Plane(cam->GetGlobalPosition(),
                          glm::cross(frontMultFar - cam->GetRight() * halfHSide, cam->GetUp()));
        leftFace = Plane(cam->GetGlobalPosition(),
                         glm::cross(cam->GetUp(), frontMultFar + cam->GetRight() * halfHSide));
        topFace = Plane(cam->GetGlobalPosition(),
                        glm::cross(cam->GetRight(), frontMultFar - cam->GetUp() * halfVSide));
        bottomFace = Plane(cam->GetGlobalPosition(),
                           glm::cross(frontMultFar + cam->GetUp() * halfVSide, cam->GetRight()));
    }
    ~Frustum() {
    }

    Plane topFace;
    Plane bottomFace;

    Plane rightFace;
    Plane leftFace;

    Plane farFace;
    Plane nearFace;
};

class Renderer : public Singleton<Renderer> {
   public:
    void UpdateMVP() {
        glPushMatrix();
        currentCamera->UpdateLoadMVP();
    }
    void Draw(Mesh3D* mesh3D) {
        glPushMatrix();

        glm::vec3 globalPos = mesh3D->GetGlobalPosition();
        glTranslatef32(floattof32(globalPos.x),
                       floattof32(globalPos.y),
                       floattof32(globalPos.z));

        glm::vec3 globalScale = mesh3D->GetGlobalScale();
        glScalef32(floattof32(globalScale.x),
                   floattof32(globalScale.y),
                   floattof32(globalScale.z));

        glm::vec3 globalRot = mesh3D->GetGlobalRotation();
        glRotateX(globalRot.x);
        glRotateY(globalRot.y);
        glRotateZ(globalRot.z);

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();

        glMatrixMode(GL_MODELVIEW);

        glMaterialf(GL_AMBIENT, RGB15(8, 8, 8));
        glMaterialf(GL_DIFFUSE, RGB15(16, 16, 16));
        glMaterialf(GL_SPECULAR, BIT(15) | RGB15(8, 8, 8));
        glMaterialf(GL_EMISSION, RGB15(5, 5, 5));

        glMaterialShinyness();

        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1 |
                  POLY_FORMAT_LIGHT2 | POLY_FORMAT_LIGHT3);

        glBindTexture(0, mesh3D->meshData->textureID);
        glBegin(GL_TRIANGLES);

        for (const Face& face : mesh3D->meshData->faces) {
            if (currentPolyCount >= 4000)
                return;
            currentPolyCount++;

            const Vertex& v1 = mesh3D->meshData->vertices[face.face1];
            const Vertex& v2 = mesh3D->meshData->vertices[face.face2];
            const Vertex& v3 = mesh3D->meshData->vertices[face.face3];

            glNormal(NORMAL_PACK(v1.normalX, v1.normalY, v1.normalZ));
            GFX_TEX_COORD = TEXTURE_PACK(v1.u, v1.v);
            glColor3f(v1.r, v1.g, v1.b);
            glVertex3v16(v1.x, v1.y, v1.z);

            glNormal(NORMAL_PACK(v2.normalX, v2.normalY, v2.normalZ));
            GFX_TEX_COORD = TEXTURE_PACK(v2.u, v2.v);
            glColor3f(v2.r, v2.g, v2.b);
            glVertex3v16(v2.x, v2.y, v2.z);

            glNormal(NORMAL_PACK(v3.normalX, v3.normalY, v3.normalZ));
            GFX_TEX_COORD = TEXTURE_PACK(v3.u, v3.v);
            glColor3f(v3.r, v3.g, v3.b);
            glVertex3v16(v3.x, v3.y, v3.z);
        }

        // Unbind the texture.
        glBindTexture(GL_TEXTURE_2D, 0);

        glEnd();

        glPopMatrix(1);
    }
    void ResetPolyCount() {
        currentPolyCount = 0;
    }
    void EndRender(){
        glPopMatrix(1);
    }
    Camera3D* currentCamera;

   private:
    int currentPolyCount = 0;
};