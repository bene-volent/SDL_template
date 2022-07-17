
#include "SDL_Wrap.h"
#include "Console.h"

void SDL_RenderDrawEllipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY)
{
	float pi = 3.14159265358979323846264338327950288419716939937510;
	float pih = pi / 2.0; //half of pi

	//drew  28 lines with   4x4  circle with precision of 150 0ms
	//drew 132 lines with  25x14 circle with precision of 150 0ms
	//drew 152 lines with 100x50 circle with precision of 150 3ms
	const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
	float theta = 0;     // angle that will be increased each loop

	//starting point
	int x = (float)radiusX * cos(theta);//start point
	int y = (float)radiusY * sin(theta);//start point
	int x1 = x;
	int y1 = y;

	//repeat until theta >= 90;
	float step = pih / (float)prec; // amount to add to theta each time (degrees)
	for (theta = step; theta <= pih; theta += step)//step through only a 90 arc (1 quadrant)
	{
		//get new point location
		x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
		y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

		//draw line from previous point to new point, ONLY if point incremented
		if ((x != x1) || (y != y1))//only draw if coordinate changed
		{
			SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1);//quadrant TR
			SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1);//quadrant TL
			SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1);//quadrant BL
			SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1);//quadrant BR
		}
		//save previous points
		x = x1;//save new previous point
		y = y1;//save new previous point
	}
	//arc did not finish because of rounding, so finish the arc
	if (x != 0)
	{
		x = 0;
		SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1);//quadrant TR
		SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1);//quadrant TL
		SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1);//quadrant BL
		SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1);//quadrant BR
	}
}

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;
	int status;


	offsetx = 0;
	offsety = radius;
	d = radius - 1;
	status = 0;

	while (offsety >= offsetx) {

		status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
			x + offsety, y + offsetx);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
			x + offsetx, y + offsety);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
			x + offsetx, y - offsety);
		status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
			x + offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}




bool SDL::init(int width,int height,const char *title)
{
	m_width = width;
	m_height = height;
	m_title = title;
	m_screen = nullptr;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Console::error("SDL Initialization Failed!");
		return false;
	}
	m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, m_width,
									m_height, SDL_WINDOW_SHOWN);

	if (!m_window)
	{
		Console::error("Window Creation Failed");
		return false;
	}
	else
	{
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	}
	return true;
}

int SDL::pollEvent()
{

	return SDL_PollEvent(&m_events);
	
}
int SDL::waitEvent()
{
	return SDL_WaitEvent(&m_events);

}

bool SDL::handlePollEvents()
{
	while (pollEvent())
	{
		switch (m_events.type)
		{
		case SDL_QUIT:
			return false;

		case SDL_MOUSEBUTTONDOWN:
			m_mouse.onPress(m_events.button.button);
			mousePressed();
			break;

		case SDL_MOUSEBUTTONUP:
			m_mouse.onRelease(m_events.button.button);
			mouseReleased();
			break;


		case SDL_MOUSEMOTION:
			m_mouse.onMove();
			mouseMotion();
			break;

		case SDL_MOUSEWHEEL:
			m_mouse.onScroll(m_events.wheel.x,  m_events.wheel.y);
			break;

		case SDL_KEYDOWN:
			m_keyboard.onPress(m_events.key.keysym.mod,
							m_events.key.keysym.scancode);
			keyPressed();
			break;
		case SDL_KEYUP:
			m_keyboard.onRelease(m_events.key.keysym.mod,
								m_events.key.keysym.scancode);
			keyReleased();
			break;

		default:
			break;
		}
	}
	return true;
}

bool SDL::handleWaitEvents()
{

	while (waitEvent())
	{
		switch (m_events.type)
		{
		case SDL_QUIT:
			return false;

		case SDL_MOUSEBUTTONDOWN:
			m_mouse.onPress(m_events.button.button);
			mousePressed();
			break;

		case SDL_MOUSEBUTTONUP:
			m_mouse.onRelease(m_events.button.button);
			mouseReleased();
			break;


		case SDL_MOUSEMOTION:
			m_mouse.onMove();
			mouseMotion();
			break;

		case SDL_MOUSEWHEEL:
			m_mouse.onScroll(m_events.wheel.x, m_events.wheel.y);
			break;

		default:
			break;
		}
		return true;
	}
	
}



void SDL::setBackground(int r,int g,int b,int a )
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b,a);
	SDL_RenderClear(m_renderer);
}
void SDL::flip()
{
	SDL_RenderPresent(m_renderer);
}



void SDL::setWindowTitle(const char* title)
{
	SDL_SetWindowTitle(m_window, title);
}

const char* SDL::getWindowTitle()
{
	return SDL_GetWindowTitle(m_window);
}

void SDL::drawRect(int x, int y, int w, int h, sdl::Color &color)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	sdl::Color prevColor;
	SDL_GetRenderDrawColor(m_renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(m_renderer, &rect);
	SDL_SetRenderDrawColor(m_renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);

}
void SDL::fillRect(int x, int y, int w, int h, sdl::Color &color)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	sdl::Color prevColor;
	SDL_GetRenderDrawColor(m_renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(m_renderer, &rect);
	SDL_SetRenderDrawColor(m_renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

void SDL::drawCircle(int x, int y, int rad, sdl::Color& color)
{
	sdl::Color prevColor;
	SDL_GetRenderDrawColor(m_renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawEllipse(m_renderer, x, y, rad, rad);
	SDL_SetRenderDrawColor(m_renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

void SDL::fillCircle(int x, int y, int rad, sdl::Color& color)
{
	sdl::Color prevColor;
	SDL_GetRenderDrawColor(m_renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillCircle(m_renderer, x, y, rad);
	SDL_SetRenderDrawColor(m_renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

void SDL::drawLine(int x1, int y1, int x2, int y2, sdl::Color& color)
{
	sdl::Color prevColor;
	SDL_GetRenderDrawColor(m_renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	SDL_SetRenderDrawColor(m_renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);

}



void SDL::tick(int frameRate)
{

	if (((SDL_GetTicks() - lastTick) < (1000 / frameRate))) {
		SDL_Delay((1000 / frameRate) - (SDL_GetTicks() - lastTick));
	}
	else
	{
		SDL_Delay(1000 / frameRate);
	}
	lastTick = SDL_GetTicks();
}

SDL::~SDL()
{
	SDL_FreeSurface(m_screen);
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
	Console::log("SDL Closed");
}



sdl::Color::Color()
{
	r = 0; g = 0; b = 0; a = 0;
}

void sdl::Color::update(Uint8 r, Uint8 g, Uint8 b, Uint8 a /*= 255*/)
{
	this->r = r; 
	this->g = g; 
	this->b = b; 
	this->a = a;
}

sdl::Color::Color(Color& color):
	r(color.r),g(color.g),b(color.b)
{

}

sdl::Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a /*= 255*/):
	r(r),g(g),b(b),a(a)
{

}
