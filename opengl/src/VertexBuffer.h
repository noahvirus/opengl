#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include <glad/glad.h>

class VBO {
public:
	GLuint ID;
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};



#endif

