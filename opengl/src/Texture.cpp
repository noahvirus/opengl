#include "Texture.h"
Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixeltype) {
	type = texType;
	int width, height, colors;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &width, &height, &colors, 0);

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0+slot);
	unit = slot;
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, pixeltype, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}
void Texture::texunit(Shader& shader, const char* uniform, GLuint unit) {
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