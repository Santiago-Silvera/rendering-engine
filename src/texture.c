#include "texture.h"
#include "shader.h"
#include <stb_image.h>
#include <stdbool.h>
#include <stdio.h>

texture_t create_texture(const char *image, GLenum textureType, GLenum slot,
                         GLenum format, GLenum pixelType) {
  texture_t texture = {.type = textureType};
  int widthImg, heightImg, numColCh;
  // flip vertically
  stbi_set_flip_vertically_on_load(true);
  unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
  if (!bytes) {
    perror("Failed to load texture\n");
  }
  if (stbi_failure_reason()) {
    printf("%s\n", stbi_failure_reason());
  }

  glGenTextures(1, &texture.textureID);

  // Docs: selects which texture unit subsequent texture
  // state calls will affect. Basically, textures come in
  // bundles and we select which texture unit to use
  glActiveTexture(slot);

  glBindTexture(textureType, texture.textureID);

  // glTexParameteri(type of texture, setting to modify, value for setting);
  glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // (r, s, t) another word for 3d axis. we dont change the R axis
  glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(textureType, 0, GL_RGBA, widthImg, heightImg, 0, format,
               pixelType, bytes);
  // Creates lower resolution versions of the texture
  glGenerateMipmap(textureType);

  stbi_image_free(bytes);
  glBindTexture(textureType, 0);

  return texture;
}

// Assigns a texture unit to a texture
void assign_texUnit(SHADER_ID *shader, const char *uniform, GLuint texUnit) {
  GLuint tex0uniform = glGetUniformLocation(*shader, uniform);
  activate_shader(shader);
  glUniform1i(tex0uniform, texUnit);
}
void bind_texture(texture_t *texture) {
  glBindTexture(GL_TEXTURE_2D, texture->textureID);
}
void unbind_texture(void) { glBindTexture(GL_TEXTURE_2D, 0); }
void delete_texture(texture_t *texture) {
  glDeleteTextures(1, &(texture->textureID));
}
