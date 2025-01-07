#pragma once

#include <nds.h>

#include <vector>

// Vertex structure to hold position, texture coordinates, and normal
struct Vertex {
    v16 x, y, z;                    // Position in 3D space (fixed-point format)
    float r, g, b;                  // Vertex Color
    t16 u, v;                       // Texture coordinates
    v10 normalX, normalY, normalZ;  // Normal vector for lighting calculations

    // Constructor to initialize all fields
    Vertex(v16 posX, v16 posY, v16 posZ, float colorR, float colorG, float colorB, t16 texU, t16 texV, v10 normX, v10 normY, v10 normZ)
        : x(posX), y(posY), z(posZ), r(colorR), g(colorG), b(colorB), u(texU), v(texV), normalX(normX), normalY(normY), normalZ(normZ) {}
};

struct Face {
    u8 face1;
    u8 face2;
    u8 face3;
    Face(u8 one, u8 two, u8 three)
        : face1(one), face2(two), face3(three) {}
};

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    int textureID;
};