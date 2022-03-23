#pragma once

#include "Alarm.hpp"

#include <iosfwd>

std::wostream& operator<<(std::wostream& os, const kjc::Alarm& a);
