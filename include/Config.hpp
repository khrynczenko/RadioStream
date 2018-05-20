#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "TextLocalizer.hpp"
#include "Language.hpp"
#include <nlohmann/json.hpp>

struct ConfigOptions
{
    LanguageCode language;
    unsigned int stations_search_limit;
    unsigned short int window_width;
    unsigned short int window_height;
};

class Config
{
public:
	explicit Config(std::string path);
    void change_language(LanguageCode code);
    void change_stations_search_limit(unsigned int limit);
    ConfigOptions get_all_config_options() const noexcept;
	~Config();
	nlohmann::json& operator[](const std::string& key);
private:
    void create_default_config_file() const;
	void save_to_file() const;
	void read_from_file();
	std::string path_;
	nlohmann::json config_;

};

#endif