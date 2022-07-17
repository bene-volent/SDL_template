#include "Mouse.h"

Mouse::Mouse()
{
	init = true;
}
int Mouse::getX()
{
	if (!init) Console::error("Mouse Not Initialized!");
	
	buttonBitmask = SDL_GetMouseState(&x, &y);
	return x;

}
Uint32 Mouse::getButtonBitmask()
{
	buttonBitmask = SDL_GetMouseState(&x, &y);
	return buttonBitmask;
}

int Mouse::getY()
{
	if (!init) Console::error("Mouse Not Initialized!");
	buttonBitmask = SDL_GetMouseState(&x, &y);
	return y;
}



void Mouse::onPress(int index)
{
	std::cout << buttons[index] << " : " << index << std::endl;

	index = getButtonIndex(index);
	buttons[index] = 1;

	std::cout << buttons[index] <<" : "<<index << std::endl;

}



void Mouse::onRelease(int index)
{
	index = getButtonIndex(index);
	buttons[index] = 0;
}

void Mouse::onScroll(int x, int y)
{
	scroll_x += x;
	scroll_y += y;
}

void Mouse::onMove()
{
	last_x = x;
	last_y = y;
	x = getX();
	y = getY();
	for (int value : buttons) 
	{
		isdragging |= value;
	}
	
}

int Mouse::deltaX()
{
	return x - last_x;
}

int Mouse::deltaY()
{
	return y - last_y;
}

int Mouse::getButtonState(int buttonIndex)
{
	if (buttonIndex >= 5) Console::error("Button index greater than Five!");

	return buttons[buttonIndex];
}

int Mouse::getButtonIndex(int index)
{

	switch (index)
	{
	case (SDL_BUTTON_LEFT):
			return 0;
	case (SDL_BUTTON_RIGHT):
			return 1;
	case (SDL_BUTTON_MIDDLE):
			return 2;
	case (SDL_BUTTON_X1):
			return 3;
	case (SDL_BUTTON_X2):
			return 4;
	default:
		break;
	}
	
	return -1;
}
