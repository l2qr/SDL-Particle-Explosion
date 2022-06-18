#pragma once
#include <SDL.h>

namespace l2qr {

class Screen
{
public:
	const static int SCREEN_WIDTH = 1900;
	const static int SCREEN_HEIGHT = 1000;
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	Uint32* m_buffer1;
	Uint32* m_buffer2;
public:
	Screen();
	bool init();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void update();
	void clear();
	void boxBlur();
	bool processEvents();
	void close();
};

} /* namespace l2qr */

