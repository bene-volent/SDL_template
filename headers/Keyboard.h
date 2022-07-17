#pragma once

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SDL.h"
#include <queue>



class Keyboard
{
private:
	const Uint8* keystates;
	std::queue<int> modsQueue;

public:
	void onPress(Uint16 mod,  SDL_Scancode scancode);
	void onRelease(Uint16 mod,  SDL_Scancode scancode);
	void setKeyStates();
};
#endif

