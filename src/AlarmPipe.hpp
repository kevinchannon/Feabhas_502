#pragma once

#include "Pipe.hpp"
#include "Alarm.hpp"

namespace kjc
{
	class AlarmPipe : public Pipe<Alarm, 20> {};
}