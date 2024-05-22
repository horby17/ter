#include "../header_files/Texture.h"
#include "../header_files/shaderClass.h"

Texture::Texture(const char* image, unsigned int texType, unsigned int slot, unsigned int format, unsigned int pixelType) {
    type = texType;

    // Assigns the texture to a Texture Unit
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(texType, ID);

    // Configures the type of algorithm used to make the image smaller or bigger
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Reads the image from a file
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generates the texture
    glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    // Deletes the image data as it is already in the OpenGL texture object
    stbi_image_free(bytes);

    // Unbinds the OpenGL texture object so that it can't accidentally be modified
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, unsigned int unit) {
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);
}

void Texture::Unbind() {
    glBindTexture(type, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &ID);
}
