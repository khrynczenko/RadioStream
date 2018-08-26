#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "TextLocalizer.hpp"
#include "Language.hpp"
#include <nlohmann/json.hpp>

struct ConfigOptions
{
    LanguageCode language = LanguageCode("en");
    unsigned short int stations_search_limit = 50u;
    unsigned short int window_width = 800u;
    unsigned short int window_height = 600u;
};

class Config
{
public:
	explicit Config(std::string path);
    void change_language(LanguageCode code);
    void change_stations_search_limit(unsigned int limit);
    ConfigOptions options() const;
	~Config();
	nlohmann::json& operator[](const std::string& key);
private:
    void create_default_config_file() const;
	void save_to_file() const;
	void read_from_file();
	std::string path_;
	nlohmann::json config_;
	const nlohmann::json default_config_;

};

#endif