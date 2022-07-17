#include "Console.h"

int Console::m_log_n = 0;

void Console::log(const char* message)
{
	std::cout << "[LOG " << ++Console::m_log_n << "] : " << message << std::endl;
}


void Console::error(const char* error)
{
	std::string message = "[Error] : ";
	message += error;
	throw(std::exception(message.c_str()));
}

