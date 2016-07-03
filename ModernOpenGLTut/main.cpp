#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <SDL2\SDL.h>
#include "Shader.h"
#include "Display.h"
#include "Mesh.h"
#include "Texture.h"
int main(int agrc, char** agrv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	std::cout << "Hello world!\n";
	Display display(800, 600, "Hello world");
	Shader shader("./res/shader");
	glEnable(GL_TEXTURE_2D);
	Texture board_bg("./res/board.png");
	Vertex data[] = {
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0,0)),
		Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0,1)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1,1))
	};
	std::cout << sizeof(Vertex) << std::endl;
	std::cout << sizeof(glm::vec3) << std::endl;
	Mesh mesh(data, sizeof(data) / sizeof(data[0]));
	while (!display.isClosed()) {
		display.Clear(0.0f, 0, 0.5f, 1.0f);

		//board_bg.bind(0);

		shader.bind();
		
		mesh.Draw();
		//glBegin(GL_TRIANGLES);
		//glTexCoord2d(0, 0);
		//glVertex3d(-0.5, -0.5, 0);
		//glTexCoord2d(1, 1);
		//glVertex3d(0, 0.5, 0);
		//glTexCoord2d(1, 0);
		//glVertex3d(0.5, -0.5, 0);
		//glEnd();

		display.Update();
	}

	std::cout << _CrtDumpMemoryLeaks() << std::endl;
	return 0;
}