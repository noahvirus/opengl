#include <ShaderClass.h>
#include <iostream>
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	std::cout << "error reading string" << std::endl;
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexcode = get_file_contents(vertexFile);
	std::string fragmentcode = get_file_contents(fragmentFile);
	const char* vertexSource = vertexcode.c_str();
	const char* fragmentSource = fragmentcode.c_str();
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//ets the shader to the source
	glShaderSource(vertexshader, 1, &vertexSource, NULL);
	//compiles shader
	glCompileShader(vertexshader);
	compileErrors(vertexshader, "VERTEX");
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentshader);
	compileErrors(fragmentshader, "FRAGMENT");
	//creates the program
	ID = glCreateProgram();
	//attaches the shaders to the program
	glAttachShader(ID, vertexshader);
	glAttachShader(ID, fragmentshader);

	//links the program
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");
	//deletes the shaders
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
}

void Shader::Activate() {
	glUseProgram(ID);
}
void Shader::Delete() {
	glDeleteProgram(ID);
}
void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hascompiled;
	char infolog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hascompiled);
		if (hascompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "Shader_Compilation_Error for: " << type << "\n" << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hascompiled);
		if (hascompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infolog);
			std::cout << "Shader_Linking_Error for: " << type << "\n" << std::endl;
		}
	}
}