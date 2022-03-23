#include "AlarmIO.hpp"

#include <iostream>

std::wostream& operator<<(std::wostream& os, const kjc::Alarm& a)
{
	os << a.as_string();

	return os;
}