#include <iostream>
#include <nana/gui.hpp>
#include "../include/Application.hpp"

int main()
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