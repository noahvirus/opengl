#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);
	void Activate();
	void Delete();
private:
	void compileErrors(unsigned int shader, const char* type);
};

class ComputeShader {
public:
	GLuint programID;
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
    ComputeShader(const std::string& computeShaderPath) {
		std::string computeShaderSource = get_file_contents(computeShaderPath.c_str());
		const char* computeShaderCode = computeShaderSource.c_str();
		GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
		glShaderSource(computeShader, 1, &computeShaderCode, nullptr);
		glCompileShader(computeShader);
		checkShaderCompilationStatus(computeShader);
		// Check for shader compilation errors here

		// Create the compute shader program
		programID = glCreateProgram();
		glAttachShader(programID, computeShader);
		glLinkProgram(programID);
		checkProgramLinkingStatus(programID);
		// Check for program linking errors here

		glDeleteShader(computeShader);
    }

    void Use() const {
        glUseProgram(programID);
    }
	// Function to check the shader compilation status
	bool checkShaderCompilationStatus(GLuint shader)
	{
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cerr << "Error: Shader compilation failed\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	// Function to check the program linking status
	bool checkProgramLinkingStatus(GLuint program)
	{
		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cerr << "Error: Program linking failed\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

    // You can add other utility functions here if needed
};

#endif