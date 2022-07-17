#pragma once

#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <stdexcept>
#include <string>

class Console
{
public:
	

	static int m_log_n;
	static void log(const char* message);
	static void error(const char* error);

	
};



#endif
