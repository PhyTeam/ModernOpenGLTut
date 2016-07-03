#include "Mesh.h"
#include <vector>
Mesh::Mesh(Vertex * vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;
	// Generate vertices data structure
	std::vector<glm::vec3> v_arr(numVertices);
	std::vector<glm::vec2> texCoord_arr(numVertices);

	for (size_t i = 0; i < numVertices; i++)
	{
		v_arr.push_back(vertices[i].getPosition());
		texCoord_arr.push_back(vertices[i].getTexCoord());
	}

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * numVertices, v_arr.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * numVertices, texCoord_arr.data(), GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}
