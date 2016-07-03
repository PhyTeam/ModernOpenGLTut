#include <glm\glm.hpp>
#include <GL\glew.h>
#include <stdio.h>
#pragma once
class Vertex
{
private:
	glm::vec3 position;
	glm::vec2 texCoord;
public:
	Vertex(const glm::vec3& pos, const glm::vec2& tc) : position(pos), texCoord(tc) {}
	Vertex(const glm::vec3& pos) : position(pos) {}
	inline glm::vec3 getPosition() const { return position; };
	inline glm::vec2 getTexCoord() const { return texCoord; };
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
		TEXCOORD_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject[NUM_BUFFERS];

	unsigned int m_drawCount;
};

