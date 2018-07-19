#ifndef STATIONLISTBOX_HPP
#define STATIONLISTBOX_HPP

#include "../../include/Station.hpp"
#include "../../include/states/State.hpp"
#include <nana/gui/widgets/listbox.hpp>
#include <vector>
#include <optional>


class StationListbox : public nana::listbox
{
public:
	enum Categories
	{
		NanaDefault,
	};
	enum Columns
	{
		Name,
        Url,
        Country,
        Language,
        Codec,
        Bitrate,
        Tags
	};
    StationListbox(nana::form& handle, State::Context context);
    void populate_listbox(const std::vector<Station>& stations);
    std::optional<Station> get_selected_station() const;
    void select_from_position(const nana::arg_mouse& arg);
private:
    void sticky_select(const nana::arg_mouse& arg);
    State::Context context_;

};

#endif