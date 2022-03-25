#pragma once

#include "AsyncPipe.hpp"
#include "AlarmList.hpp"

#include <gsl/gsl>

namespace kjc
{
	class AlarmPipe : private AsyncPipe<AlarmList, 20>
	{
	public:
		AlarmPipe();
		AlarmPipe(const AlarmPipe&) = delete;
		AlarmPipe(AlarmPipe&&) = delete;
		AlarmPipe& operator=(const AlarmPipe&) = delete;
		AlarmPipe& operator=(AlarmPipe&&) = delete;

		using Base_t = AsyncPipe<AlarmList, 20>;

		using Base_t::pull;
		using Base_t::push;
		using Base_t::set_item_arrived_callback;
		using Base_t::is_empty;
		using Base_t::is_full;
	};
}