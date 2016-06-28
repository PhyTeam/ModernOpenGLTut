#include "Display.h"
#include <GL\glew.h>
#include <iostream>
Display::Display(int width, int height, const std::string & title)
{
	m_isClosed = false;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_Context = SDL_GL_CreateContext(m_Window);

	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cout << "GLEW initialized err" << std::endl;
	}
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Display::onResize(int width, int height)
{
}

void Display::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_Window);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			m_isClosed = true;
	}
}
