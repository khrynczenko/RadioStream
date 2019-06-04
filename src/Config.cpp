#include "../include/Config.hpp"
#include "../include/Language.hpp"
#include <fstream>

Config::Config(const std::filesystem::path& path_to_config)
	: path_to_config_(path_to_config)
	, default_config_( {
        {"language", "en"},
        {"stations_search_limit", 50},
        {"width", 976},
        {"height", 600}})
{
    if (!std::filesystem::exists(path_to_config_))
    {
        create_default_config_file();
    }
    read_from_file();
}

void Config::change_language(const LanguageCode& code)
{
    config_["language"] = code.as_string();
}

void Config::change_stations_search_limit(unsigned int limit)
{
    config_["stations_search_limit"] = limit;
}

ConfigOptions Config::options() const
{
    ConfigOptions options;
    options.language = LanguageCode(config_["language"].get<std::string>());
    options.stations_search_limit = config_["stations_search_limit"].get<unsigned short int>();
    options.window_height = config_["height"].get<unsigned short int>();
    options.window_width = config_["width"].get<unsigned short int>();
    return options;
}

Config::~Config()
{
	save_to_file();
}

void Config::create_default_config_file() const
{
    std::ofstream output(path_to_config_);
    output << default_config_.dump(4);
}

void Config::save_to_file() const
{
	std::ofstream output(path_to_config_);
	output << config_.dump(4);
}

void Config::read_from_file()
{
	std::ifstream input(path_to_config_);
	input >> config_;
}

nlohmann::json& Config::operator[](const std::string& key)
{
	return config_[key];
}
