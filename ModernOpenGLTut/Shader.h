#include <GL\glew.h>
#include <string>

#ifndef SHADER_H__
#define SHADER_H__

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	void	bind();
private:
	Shader(Shader& other) {};
	void operator=(const Shader& other) {};
	static const unsigned int NUM_SHADER = 2;
	GLuint m_Program;
	GLuint m_Shaders[NUM_SHADER];
};

#endif // SHADER_H__