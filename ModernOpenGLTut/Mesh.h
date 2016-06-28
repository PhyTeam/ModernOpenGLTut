#include <glm\glm.hpp>
#include <GL\glew.h>
#include <stdio.h>
#pragma once
class Vertex
{
private:
	glm::vec3 position;
public:
	Vertex(const glm::vec3& pos) : position(pos) {}
	~Vertex() {}
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh();

	void Draw();

private:
	Mesh(const Mesh& other) = delete;
	void operator=(const Mesh& other) = delete;
	enum
	{
		POSITION_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject[NUM_BUFFERS];

	unsigned int m_drawCount;
};

