#ifndef RADIOSTREAM_APPLICATIONDIRECTORIES_HPP
#define RADIOSTREAM_APPLICATIONDIRECTORIES_HPP

#include <filesystem>

[[nodiscard]] std::filesystem::path get_home_path();

[[nodiscard]] std::filesystem::path get_config_directory_path();

[[nodiscard]] std::filesystem::path get_data_directory_path();

[[nodiscard]] std::filesystem::path get_lang_directory_path() noexcept;

#endif  // RADIOSTREAM_APPLICATIONDIRECTORIES_HPP
