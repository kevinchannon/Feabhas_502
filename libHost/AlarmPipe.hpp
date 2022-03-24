#pragma once

#include "Pipe.hpp"
#include "AlarmList.hpp"

namespace kjc
{
	class AlarmPipe : Pipe<AlarmList, 20>
	{
	public:
		AlarmPipe();
		AlarmPipe(const AlarmPipe&) = delete;
		AlarmPipe(AlarmPipe&&) = delete;
		AlarmPipe& operator=(const AlarmPipe&) = delete;
		AlarmPipe& operator=(AlarmPipe&&) = delete;

		using Base_t = Pipe<AlarmList, 20>;

		using Base_t::pull;
		using Base_t::push;
	};
}