#include "../include/Config.hpp"
#include "../include/Language.hpp"
#include <fstream>
#include <experimental/filesystem>

Config::Config(std::string path)
	: path_(std::move(path))
	, default_config_( {
        {"language", "en"},
        {"stations_search_limit", 50},
        {"width", 976},
        {"height", 600}})
{
    if (!std::experimental::filesystem::exists(path_))
    {
        create_default_config_file();
    }
    read_from_file();
}

void Config::change_language(LanguageCode code)
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
    std::ofstream output(path_);
    output << default_config_.dump(4);
}

void Config::save_to_file() const
{
	std::ofstream output(path_);
	output << config_.dump(4);
}

void Config::read_from_file()
{
	std::ifstream input(path_);
	input >> config_;
}

nlohmann::json& Config::operator[](const std::string& key)
{
	return config_[key];
}
