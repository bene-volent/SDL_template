#pragma once
#ifndef MOUSE_H
#define MOUSE_H
#include "SDL.h"
#include "Console.h"

class Mouse
{
public:
	int x, y,last_x,last_y,scroll_x,scroll_y;
	bool isdragging = false;
	int buttons[5] = { 0,0,0,0,0 };
	Uint32 buttonBitmask;
	char name[10] = "Mouse";
public:
	Mouse();
	int getX();
	Uint32 getButtonBitmask();
	int getY();

	void onPress(int index);

	void onRelease(int index);

	void onScroll(int x, int y);
	void onMove();
	void reset();

	int deltaX();
	int deltaY();

	int getButtonState(int buttonIndex);




private:
	bool init = false;

	int getButtonIndex(int index);
};


#endif
