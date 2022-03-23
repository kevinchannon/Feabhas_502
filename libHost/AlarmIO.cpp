#include "AlarmIO.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const kjc::Alarm& a)
{
	os << a.as_string();

	return os;
}