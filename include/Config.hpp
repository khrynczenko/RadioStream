#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <nlohmann/json.hpp>

class Config
{
public:
	explicit Config(std::string path);
	~Config();
	nlohmann::json& operator[](const std::string& key);
private:
	void save_to_file() const;
	void read_from_file();
	std::string path_;
	nlohmann::json config_;

};

#endif