#include <iostream>
#include "Screen.h"

namespace l2qr {

	Screen::Screen() :
		m_window(NULL),
		m_renderer(NULL),
		m_texture(NULL),
		m_buffer1(NULL),
		m_buffer2(NULL)
	{
	}

	bool Screen::init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			return false;
		}
		m_window = SDL_CreateWindow("Particle Fire Explosion",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (m_window == NULL) {
			SDL_Quit();
			return false;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (m_renderer == NULL) {
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (m_texture == NULL) {
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}
		m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

		memset(m_buffer1, 0, sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);
		memset(m_buffer2, 0, sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);

		update();
		return true;
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{
		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;
		m_buffer1[(y * SCREEN_WIDTH) + x] = color;
	}

	void Screen::update()
	{		
		SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	void Screen::clear()
	{
		memset(m_buffer1, 0, sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);
		memset(m_buffer2, 0, sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);
	}

	bool Screen::processEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	}

	void Screen::boxBlur()
	{
		auto temp = m_buffer1;
		m_buffer1 = m_buffer2;
		m_buffer2 = temp;

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				int red = 0;
				int green = 0;
				int blue = 0;

				for (short row = -1; row <= 1; row++) {
					for (short col = -1; col <= 1; col++) {
						int currentX = x + col;
						int currentY = y + row;
						if (currentX >= 0 && currentX < SCREEN_WIDTH 
							&& currentY >= 0 && currentY < SCREEN_HEIGHT) {
							Uint32 rgba = m_buffer2[currentY * SCREEN_WIDTH + currentX];

							red += (unsigned char)(rgba >> 24);
							green += (unsigned char)(rgba >> 16);
							blue += (unsigned char)(rgba >> 8);							
						}
					}
				}
				red /= 9;
				green /= 9;
				blue /= 9;

				setPixel(x, y, red, green, blue);
			}
		}
	}

	void Screen::close()
	{
		delete[] m_buffer1;
		delete[] m_buffer2;

		SDL_DestroyTexture(m_texture);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
} /* namespace l2qr */