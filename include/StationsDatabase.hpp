#ifndef STATIONSDATABASE_HPP
#define STATIONSDATABASE_HPP

#include "Station.hpp"
#include "Subject.hpp"
#pragma warning(push, 0)
#include <Poco/Data/Session.h>
#pragma warning(pop)
#include <filesystem>

class StationsDatabase : public Subject {
   public:
    explicit StationsDatabase(const std::filesystem::path& path_to_db_file);
    [[nodiscard]] const std::vector<Station>& get_stations() const noexcept;
    void add_station(const Station& station);
    void remove_station(const Station& station);
    std::vector<Station> get_stations_by_substring(
        const std::string& substring) const;

   private:
    void create_empty_table_if_does_not_exist();
    void cache_stations_stored_in_database();
    Poco::Data::Session database_;
    std::vector<Station> cached_stations_;
};

#endif
