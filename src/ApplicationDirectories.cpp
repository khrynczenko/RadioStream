#include "../include/ApplicationDirectories.hpp"

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

std::filesystem::path get_lang_directory_path() noexcept
{
#ifndef _WIN32
    return "/usr/local/share/radiostream";
#else
    return std::filesystem::current_path();
#endif
}
