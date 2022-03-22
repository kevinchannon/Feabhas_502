#pragma once

#include "Pipe.hpp"
#include "Alarm.hpp"

namespace kjc
{
	template<size_t k_max_messages>
	using AlarmPipe = Pipe<Alarm, k_max_messages>;
}