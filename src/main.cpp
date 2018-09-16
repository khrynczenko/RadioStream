#include "../include/Application.hpp"
#include "Poco/Data/SQLite/Connector.h"
#include <nana/gui.hpp>
#include <iostream>

#ifndef _WIN32
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#ifndef _WIN32

std::filesystem::path get_home_path()
{
    const char* home_path = getenv("HOME");
    if (home_path == NULL) {
        home_path = getpwuid(getuid())->pw_dir;
    }
    return home_path;
}

#endif
std::filesystem::path get_config_directory_path()
{
#ifndef _WIN32
    const char* config_path = getenv("XDG_CONFIG_HOME");
    if (config_path == NULL) {
        config_path = ".config/radiostream";
    }
    return get_home_path() / config_path;
#else
    return std::filesystem::current_path();
#endif
}

std::filesystem::path get_data_directory_path()
{
#ifndef _WIN32
    const char* data_path = getenv("XDG_DATA_HOME");
    if (data_path == NULL) {
        data_path = ".local/share/radiostream";
    }
    return get_home_path() / data_path;
#else
    return std::filesystem::current_path();
#endif
}

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
    auto config_path = get_config_directory_path();
    auto data_path = get_data_directory_path();
    std::filesystem::create_directories(config_path);
    std::filesystem::create_directories(data_path);
    Poco::Data::SQLite::Connector::registerConnector();
	try {
		Application app{config_path, data_path};
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
