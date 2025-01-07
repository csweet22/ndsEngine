#pragma once

#include <vector>
#include <nds.h>
#include "MeshData.h"

std::vector<Vertex> cubeColorVertices = {
    // Bottom face vertices
    Vertex(floattov16(-0.5), floattov16(-0.5), floattov16(0.5), 1.0f, 1.0f, 1.0f, inttot16(0), inttot16(128), floattov10(0), floattov10(-1), floattov10(0)),   // 0
    Vertex(floattov16(0.5), floattov16(-0.5), floattov16(0.5), 1.0f, 0.0f, 0.0f, inttot16(128), inttot16(128), floattov10(0), floattov10(-1), floattov10(0)),  // 1
    Vertex(floattov16(0.5), floattov16(-0.5), floattov16(-0.5), 0.0f, 1.0f, 0.0f, inttot16(128), inttot16(0), floattov10(0), floattov10(-1), floattov10(0)),   // 2
    Vertex(floattov16(-0.5), floattov16(-0.5), floattov16(-0.5), 0.0f, 0.0f, 1.0f, inttot16(0), inttot16(0), floattov10(0), floattov10(-1), floattov10(0)),    // 3

    // Top face vertices
    Vertex(floattov16(-0.5), floattov16(0.5), floattov16(0.5), 1.0f, 1.0f, 1.0f, inttot16(0), inttot16(128), floattov10(0), floattov10(1), floattov10(0)),   // 4
    Vertex(floattov16(0.5), floattov16(0.5), floattov16(0.5), 1.0f, 0.0f, 0.0f, inttot16(128), inttot16(128), floattov10(0), floattov10(1), floattov10(0)),  // 5
    Vertex(floattov16(0.5), floattov16(0.5), floattov16(-0.5), 0.0f, 1.0f, 0.0f, inttot16(128), inttot16(0), floattov10(0), floattov10(1), floattov10(0)),   // 6
    Vertex(floattov16(-0.5), floattov16(0.5), floattov16(-0.5), 0.0f, 0.0f, 1.0f, inttot16(0), inttot16(0), floattov10(0), floattov10(1), floattov10(0)),    // 7
};

std::vector<Face> cubeFaces = {
    // Bottom face
    Face(0, 2, 1),
    Face(0, 3, 2),

    // Top face
    Face(4, 5, 6),
    Face(4, 6, 7),

    // Front face
    Face(0, 1, 5),
    Face(0, 5, 4),

    // Back face
    Face(3, 7, 6),
    Face(3, 6, 2),

    // Left face
    Face(0, 4, 7),
    Face(0, 7, 3),

    // Right face
    Face(1, 2, 6),
    Face(1, 6, 5),
};