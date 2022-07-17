#pragma once

#ifndef SDL_HANDLER_H
#define SDL_HANDLER_H

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Mouse.h"
#include "Keyboard.h"


void SDL_RenderDrawEllipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY);
int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius);

namespace sdl {
	class Color
	{
	public:
		Uint8 r, g, b, a;

	public :
		Color();
		Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		Color(Color& color);
		void update(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		
		
	};

}


class SDL {

public:
	// Public Field

	// SDL Fields
	SDL_Window* m_window = nullptr;
	SDL_Surface *m_screen = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Event m_events;

	// Local Class Fields
	Mouse m_mouse;
	Keyboard m_keyboard;
	int m_width, m_height;
	const char* m_title;

public:
	// Public Methods

	bool init(int width, int height, const char* title);
	

	int pollEvent();
	int waitEvent();
	bool handlePollEvents();
	bool handleWaitEvents();
	
	virtual void mousePressed() {}
	virtual void mouseReleased(){}
	virtual void mouseMotion()  {}
	virtual void keyPressed()   {}
	virtual void keyReleased()  {}

	void setBackground(int r,int g,int b,int a =255);
	void flip();
	void setWindowTitle(const char* title);
	const char* getWindowTitle();


	void drawRect(int x, int y, int w, int h, sdl::Color &color);
	void fillRect(int x, int y, int w, int h, sdl::Color &color);
	void drawCircle(int x, int y, int rad, sdl::Color& color);
	void fillCircle(int x, int y, int rad, sdl::Color& color);
	void drawLine(int x1, int y1, int x2, int y2, sdl::Color& color);
	

	void tick(int frameRate);

	~SDL();


private:
	int lastTick = 0;
};

#endif