#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>
#include "../header_files/shaderClass.h"

class Texture {
public:
    GLuint ID;
    GLenum type;
    unsigned int unit;

    Texture(const char* image, unsigned int texType, unsigned int slot, unsigned int format, unsigned int pixelType);

    void texUnit(Shader& shader, const char* uniform, unsigned int unit);
    void Bind();
    void Unbind();
    void Delete();
};

#endif
