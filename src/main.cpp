#include <iostream>
#include <nana/gui.hpp>
#include "../include/Application.hpp"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
//int main
{
	
	try {
		Application app{};
		nana::exec();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	catch (...)
	{
		std::cout << "Unidentified exception.";
	}
}