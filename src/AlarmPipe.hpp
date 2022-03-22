#pragma once

#include "Pipe.hpp"
#include "Alarm.hpp"

namespace kjc
{
	class AlarmPipe : public Pipe<Alarm, 20>
	{
	public:
		AlarmPipe();
		AlarmPipe(const AlarmPipe&) = delete;
		AlarmPipe(AlarmPipe&&) = delete;
		AlarmPipe& operator=(const AlarmPipe&) = delete;
		AlarmPipe& operator=(AlarmPipe&&) = delete;
	};
}