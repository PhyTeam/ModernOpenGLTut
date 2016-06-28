#include <string>
#include <gl\glew.h>
#pragma once
class Texture
{
public:
	Texture(const std::string& fileName);
	virtual ~Texture();

	void bind(unsigned int unit);
protected:
private:
	GLuint m_Texture;
};

