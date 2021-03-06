#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "TextLocalizer.hpp"
#include "Language.hpp"
#pragma warning(push, 0)
#include <nlohmann/json.hpp>
#pragma warning(pop, 0)
#include <filesystem>

struct ConfigOptions {
    LanguageCode language = LanguageCode("en");
    unsigned short int stations_search_limit = 50u;
    unsigned short int window_width = 800u;
    unsigned short int window_height = 600u;
};

class Config {
   public:
    explicit Config(const std::filesystem::path& path_to_config);
    void change_language(const LanguageCode& code);
    void change_stations_search_limit(unsigned int limit);
    [[nodiscard]] ConfigOptions options() const;
    ~Config();
    [[nodiscard]] nlohmann::json& operator[](const std::string& key);

   private:
    void create_default_config_file() const;
    void save_to_file() const;
    void read_from_file();
    std::filesystem::path path_to_config_;
    nlohmann::json config_;
    const nlohmann::json default_config_;
};

#endif