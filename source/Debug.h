#pragma once

#include "Engine.h"

class Debug {
   public:
    static void DrawQuad(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1), glm::vec3 color = glm::vec3(1, 0, 0), bool filled = true, float offset = 0.1) {
        if (filled) {
            glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

            glPushMatrix();

            glTranslatef32(floattof32(position.x),
                           floattof32(position.y),
                           floattof32(position.z));

            glScalef32(floattof32(scale.x),
                       floattof32(scale.y),
                       floattof32(scale.z));

            glRotateXi(inttof32((int)rotation.x));
            glRotateYi(inttof32((int)rotation.y));
            glRotateZi(inttof32((int)rotation.z));

            glMatrixMode(GL_MODELVIEW);

            glBegin(GL_QUAD);

            glColor3b((u8)(color.r * 255.0f), (u8)(color.g * 255.0f), (u8)(color.b * 255.0f));
            glVertex3v16(floattov16(-0.5), floattov16(0.5), floattov16(0));
            glVertex3v16(floattov16(0.5), floattov16(0.5), floattov16(0));
            glVertex3v16(floattov16(0.5), floattov16(-0.5), floattov16(0));
            glVertex3v16(floattov16(-0.5), floattov16(-0.5), floattov16(0));

            glEnd();

            glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK);

            glPopMatrix(1);

        } else {
        }
    }

    static void DrawLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 color, float offset = 0.1) {
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

        glBegin(GL_QUAD);

        glColor3f(color.r, color.g, color.b);
        glVertex3v16(floattov16(p1.x), floattov16(p1.y), floattov16(p1.z));
        glVertex3v16(floattov16(p1.x + offset), floattov16(p1.y + offset), floattov16(p1.z + offset));
        glVertex3v16(floattov16(p2.x), floattov16(p2.y), floattov16(p2.z));
        glVertex3v16(floattov16(p2.x + offset), floattov16(p2.y + offset), floattov16(p2.z + offset));

        glEnd();

        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK);
    }
};