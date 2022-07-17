#include "Keyboard.h"

void Keyboard::onPress(Uint16 mod,SDL_Scancode scancode)
{
	setKeyStates();
	
	modsQueue.push(mod);
}

void Keyboard::onRelease(Uint16 mod,  SDL_Scancode scancode)
{
	setKeyStates();
	modsQueue.pop();
}

void Keyboard::setKeyStates()
{
	keystates = SDL_GetKeyboardState(NULL);
}
