#include <string>
#include <SDL2\SDL.h>

#ifndef DISPLAY_H__
#define DISPLAY_H__

class Display
{
public:
	Display(int width, int height, const std::string& title);

	virtual ~Display();

	void onResize(int width, int height);
	inline bool isClosed() { return m_isClosed; };
	void Clear();
	void Clear(float r, float g, float b, float a);
	void Update();
private:
	Display(Display& other) = delete;
	Display& operator=(const Display& other) = delete;

	SDL_Window* m_Window;
	SDL_GLContext m_Context;
	bool m_isClosed;
};
#endif // !DISPLAY_H__