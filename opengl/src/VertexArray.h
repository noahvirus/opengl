#ifndef VAO_BUFFER_H
#define VAO_BUFFER_H
#include <glad/glad.h>
#include <VertexBuffer.h>
class VAO {
public:
	GLuint ID;
	VAO();

	void LinkAttrib(VBO& vbo, GLuint layout, GLuint numcomponents, GLenum type,GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};



#endif