#ifndef RADIOSTREAM_APPLICATIONDIRECTORIES_HPP
#define RADIOSTREAM_APPLICATIONDIRECTORIES_HPP

#include <filesystem>

std::filesystem::path get_home_path();

std::filesystem::path get_config_directory_path();

std::filesystem::path get_data_directory_path();


#endif //RADIOSTREAM_APPLICATIONDIRECTORIES_HPP
