#include "../include/Application.hpp"
#include "Poco/Data/SQLite/Connector.h"
#include <nana/gui.hpp>
#include <iostream>

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
    Poco::Data::SQLite::Connector::registerConnector();
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
