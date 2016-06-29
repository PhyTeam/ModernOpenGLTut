#include "Shader.h"
#include <fstream>
#include <GL\glew.h>
#include <iostream>
static std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLint shader, GLint flag, bool isProgram, const std::string& error_message);
static GLint CreateShader(const std::string& text, GLenum type);

Shader::Shader(const std::string & fileName)
{
	m_Program = glCreateProgram();
	m_Shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_Shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (size_t i = 0; i < NUM_SHADER; i++)
	{
		glAttachShader(m_Program, m_Shaders[i]);
	}
	glBindAttribLocation(m_Program, 0, "Position");
	glBindAttribLocation(m_Program, 1, "TexCoord");
	glUniform1i(glGetUniformLocation(m_Program, "gSampler"), 0);

	glLinkProgram(m_Program);
	CheckShaderError(m_Program, GL_LINK_STATUS, true, "SHADER LINK ERROR");
	glValidateProgram(m_Program);
	CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "INVALID SHADER");
}

Shader::~Shader()
{
	// Not need !!
	for (size_t i = 0; i < NUM_SHADER; i++)
	{
		glAttachShader(m_Program, m_Shaders[i]);
		glDeleteShader(m_Shaders[i]);
	}
	glDeleteProgram(m_Program);
}

void Shader::bind()
{
	glUseProgram(m_Program);
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream in;
	in.open(fileName.c_str());

	std::string output;
	std::string line;

	if (in.is_open()) 
	{
		while (in.good())
		{
			std::getline(in, line);
			output.append(line + '\n');
		}
	}
	else
	{
		std::cout << "Unable to load shader: " << fileName << std::endl;
	}
	return output;
}

void CheckShaderError(GLint shader, GLint flag, bool isProgram, const std::string& error_message)
{
	GLint success = 0;
	GLchar message[1024];

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(message), NULL, message);
		else
			glGetShaderInfoLog(shader, sizeof(message), NULL, message);

		std::cerr << error_message << ": '" << message << "'" << std::endl;
	}
}

GLint CreateShader(const std::string & text, GLenum type)
{
	GLint shader = glCreateShader(type);
	if (shader == 0)
		std::cerr << "Can't create shader " << text << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation error\n");
	
	return shader;
}
