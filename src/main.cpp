#include "../include/Application.hpp"
#include <nana/gui.hpp>
#include <iostream>
#include <string>

#ifdef _WIN32 
    #ifndef _DEBUG
        int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
    #else
        int main()
    #endif
#else
    int main()
#endif
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