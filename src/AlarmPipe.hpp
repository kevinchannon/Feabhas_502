#pragma once

#include "Pipe.hpp"
#include "Alarm.hpp"

namespace kjc
{
	template<size_t MAX_MESSAGES>
	using AlarmPipe = Pipe<Alarm, MAX_MESSAGES>;
}