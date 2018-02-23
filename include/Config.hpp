#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "TextLocalizer.hpp"
#include "Language.hpp"
#include <nlohmann/json.hpp>

class Config
{
public:
	explicit Config(std::string path);
    void change_language(LanguageCode code);
	~Config();
	nlohmann::json& operator[](const std::string& key);
private:
	void save_to_file() const;
	void read_from_file();
	std::string path_;
	nlohmann::json config_;

};

#endif