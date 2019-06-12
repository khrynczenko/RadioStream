#include "../../include/widgets/StationListbox.hpp"
#include <nana/gui/widgets/form.hpp>

StationListbox::StationListbox(nana::form& handle, State::Context context)
    : nana::listbox(handle)
    , context_(context)
{
    this->append_header(context_.localizer_.get_localized_text("Station's name"));
    this->append_header(context_.localizer_.get_localized_text("URL"));
    this->append_header(context_.localizer_.get_localized_text("Country"));
    this->append_header(context_.localizer_.get_localized_text("Language"));
    this->append_header(context_.localizer_.get_localized_text("Codec"));
    this->append_header(context_.localizer_.get_localized_text("Bitrate"));
    this->append_header(context_.localizer_.get_localized_text("Tags"));
    this->column_at(Columns::Name).width(300u);
    this->column_at(Columns::Url).width(200u);
    this->column_at(Columns::Country).width(100u);
    this->column_at(Columns::Language).width(100u);
    this->column_at(Columns::Codec).width(50u);
    this->column_at(Columns::Bitrate).width(100u);
    this->column_at(Columns::Tags).width(100u);
    this->enable_single(false, false);
	this->set_sort_compare(Columns::Bitrate, this->bitrate_comparator);
}

void StationListbox::populate_listbox(const std::vector<Station>& stations)
{
    this->auto_draw(false);
    this->clear();
	const auto category_index = Categories::NanaDefault;
	std::for_each(stations.cbegin(), stations.cend(), [&stations](const auto& station) {
		this->at(category_index).append(station);
	});
    this->auto_draw(true);
}

std::optional<Station> StationListbox::get_selected_station() const
{
    if (!this->selected().empty())
    {
        const auto selected_item = this->selected().front();
        const auto category_index = static_cast<std::size_t>(Categories::NanaDefault);
        const auto column_index = static_cast<std::size_t>(Columns::Name);
        const auto station_category = this->at(category_index);
        const auto name = station_category.at(selected_item.item).text(column_index);
        const auto url = station_category.at(selected_item.item).text(static_cast<std::size_t>(Columns::Url));
        const auto country = station_category.at(selected_item.item).text(static_cast<std::size_t>(Columns::Country));
        const auto language = station_category.at(selected_item.item).text(static_cast<std::size_t>(Columns::Language));
        const auto codec = station_category.at(selected_item.item).text(static_cast<std::size_t>(Columns::Codec));
        const auto bitrate = station_category.at(selected_item.item).text(static_cast<std::size_t>(Columns::Bitrate));
        const auto tags = station_category.at(selected_item.item).text(static_cast<std::size_t>(Columns::Tags));
        return std::make_optional<Station>(name, url, country, language, codec, bitrate, tags);
    }
    return std::nullopt;
    
}

/**
* \brief custom nana comparator for storting station listbox by bitrate in correct manner
*/
bool StationListbox::bitrate_comparator(const std::string& lhs, nana::any* any_l, const std::string& rhs, nana::any* any_r, bool reverse)
{
	try
	{
		int lhs_bitrate = std::stoi(lhs);
		int rhs_bitrate = std::stoi(rhs);
		return reverse ? lhs_bitrate  > rhs_bitrate  : lhs_bitrate  < rhs_bitrate ;
	}
	catch (const std::invalid_argument&)
	{
		return true; // We don't want to terminate the program just because there is some non-convertible value
	}
}

void StationListbox::sticky_select(const nana::arg_mouse& arg)
{
    if (!this->selected().empty())
    {
        for (const auto& pair : this->selected())
        {
            if (pair.item == this->selected().front().item)
            {
                continue;
            }
            else
            {
                this->at(pair.cat).at(pair.item).select(false);
            }
        }
    }
}
