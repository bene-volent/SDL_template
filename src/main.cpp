// SDL_template.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Console.h"
#include "SDL_Wrap.h"
#include "Mouse.h"



class Window :public SDL 
{
public:
    
    virtual void mouseMotion() override {
        std::cout << "Mouse Position : [ " << m_mouse.getX() << " , " << m_mouse.getY() << " ]\n";
    }
	virtual void mousePressed() override {
		std::cout << "Mouse Position : [ " << m_mouse.getX() << " , " << m_mouse.getY() << " ] " << m_mouse.getButtonState(0)<<"\n";
	}
	virtual void  mouseReleased() override {
		std::cout << "Mouse Position : [ " << m_mouse.getX() << " , " << m_mouse.getY() << " ]\n";
	}

};


int main()
{
    

    Window window;
    window.init(640, 640, "Test Window");
    int begin = 0;
    while (window.handlePollEvents()) 
    {   
		sdl::Color tmp(100, 22, 201);

        window.setBackground(240, 132, 34);
		sdl::Color rectColor(100, 100, 40);

		window.fillCircle(200, 200, 200, tmp);
        tmp.update(192, 43, 121);

		window.drawCircle(200, 200, 200, tmp);

        window.flip();
        window.tick(60);
        //std::string str = "FPS : "  +std::to_string (1000.0f/(SDL_GetTicks() - begin));
        begin = SDL_GetTicks();
        //Console::log(str.c_str());
        
    }
    
}
