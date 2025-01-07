#pragma once

#include <vector>
#include <nds.h>
#include "MeshData.h"

std::vector<Vertex> cubeVertices = {
    // Bottom face vertices
    Vertex(floattov16(-0.5), floattov16(-0.5), floattov16(0.5), 1.0f, 1.0f, 1.0f, inttot16(0), inttot16(128), floattov10(0), floattov10(-1), floattov10(0)),   // 0
    Vertex(floattov16(0.5), floattov16(-0.5), floattov16(0.5), 1.0f, 1.0f, 1.0f, inttot16(128), inttot16(128), floattov10(0), floattov10(-1), floattov10(0)),  // 1
    Vertex(floattov16(0.5), floattov16(-0.5), floattov16(-0.5), 1.0f, 1.0f, 1.0f, inttot16(128), inttot16(0), floattov10(0), floattov10(-1), floattov10(0)),   // 2
    Vertex(floattov16(-0.5), floattov16(-0.5), floattov16(-0.5), 1.0f, 1.0f, 1.0f, inttot16(0), inttot16(0), floattov10(0), floattov10(-1), floattov10(0)),    // 3

    // Top face vertices
    Vertex(floattov16(-0.5), floattov16(0.5), floattov16(0.5), 1.0f, 1.0f, 1.0f, inttot16(0), inttot16(128), floattov10(0), floattov10(1), floattov10(0)),   // 4
    Vertex(floattov16(0.5), floattov16(0.5), floattov16(0.5), 1.0f, 1.0f, 1.0f, inttot16(128), inttot16(128), floattov10(0), floattov10(1), floattov10(0)),  // 5
    Vertex(floattov16(0.5), floattov16(0.5), floattov16(-0.5), 1.0f, 1.0f, 1.0f, inttot16(128), inttot16(0), floattov10(0), floattov10(1), floattov10(0)),   // 6
    Vertex(floattov16(-0.5), floattov16(0.5), floattov16(-0.5), 1.0f, 1.0f, 1.0f, inttot16(0), inttot16(0), floattov10(0), floattov10(1), floattov10(0)),    // 7
};