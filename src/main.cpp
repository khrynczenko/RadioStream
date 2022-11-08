#include "../include/Application.hpp"
#include "../include/ApplicationDirectories.hpp"
#pragma warning(push, 0)
#include <Poco/Data/SQLite/Connector.h>
#include <nana/gui.hpp>
#pragma warning(pop)
#include <iostream>

#ifdef _WIN32
#ifndef _DEBUG
int WinMain([[maybe_unused]] HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, char*,
            [[maybe_unused]] int nShowCmd)
#else
int main()
#endif
#else
int main()
#endif
{
    auto config_path = get_config_directory_path();
    auto data_path = get_data_directory_path();
    auto lang_path = get_lang_directory_path();
    std::filesystem::create_directories(config_path);
    std::filesystem::create_directories(data_path);
    Poco::Data::SQLite::Connector::registerConnector();
    try {
        Application app{config_path, data_path, lang_path};
        nana::exec();
    } catch (std::exception& e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "Unidentified exception.";
    }
}
