#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "TextLocalizer.hpp"
#include "Language.hpp"
#pragma warning(push, 0)
#include <nlohmann/json.hpp>
#pragma warning(pop, 0)
#include <filesystem>

constexpr std::uint16_t DEFAULT_STATION_SEARCH_LIMIT = 50;
constexpr std::uint16_t DEFAULT_WINDOW_WIDTH = 800;
constexpr std::uint16_t DEFAULT_WINDOW_HEIGHT = 600;

struct ConfigOptions {
    LanguageCode language = LanguageCode("en");
    unsigned short int stations_search_limit = DEFAULT_STATION_SEARCH_LIMIT;
    unsigned short int window_width = DEFAULT_WINDOW_WIDTH;
    unsigned short int window_height = DEFAULT_WINDOW_HEIGHT;
};

class Config {  // NOLINT: Destructor does not manage resource, just saves a file
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
