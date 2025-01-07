#pragma once

#include <nds.h>
#include <stdio.h>

class TextureData {
   public:
    TextureData(GL_TEXTURE_TYPE_ENUM colorType, int xSize, int ySize, int param, u8* textureBinary) {
        textureID = 0;
        glGenTextures(1, &textureID);
        // assert(textureID != 0);
        glBindTexture(0, textureID);
        glTexImage2D(0, 0, colorType, xSize, ySize, 0, param, textureBinary);
    }
    ~TextureData() {
        if (textureID != 0)
            glDeleteTextures(1, &textureID);
    }
    int GetTextureID() {
        return textureID;
    }

   private:
    int textureID;
};
