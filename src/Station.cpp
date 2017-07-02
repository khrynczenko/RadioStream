#include "../include/Station.hpp"

Station::Station(const std::string& name, const std::string& ip, bool favorite, bool user_defined)
	: name_(name)
	, ip_(ip)
	, favorite_(favorite)
	, user_defined_(user_defined)

{
}

Station::Station(const Station& rhs)
	: name_(rhs.name_)
	, ip_(rhs.ip_)
	, favorite_(rhs.favorite_)
	, user_defined_(rhs.user_defined_)
{
}

Station& Station::operator=(const Station& rhs)
{
	if (this == &rhs)
		return *this;
	const_cast<std::string&>(name_) = rhs.name_;
	const_cast<std::string&>(ip_) = rhs.ip_;
	favorite_ = rhs.favorite_;
	user_defined_ = rhs.user_defined_;
	return *this;

}

bool Station::operator==(const Station& rhs) const
{
	if (name_ == rhs.name_ && ip_ == rhs.ip_)
		return true;
	return false;
}

