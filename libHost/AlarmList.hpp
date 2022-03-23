#pragma once

#include "Alarm.hpp"

#include <vector>

namespace kjc
{
class AlarmList : protected std::vector<Alarm>
{
public:
	AlarmList() noexcept = default;
	~AlarmList() noexcept = default;

	AlarmList(const AlarmList&) = delete;
	AlarmList& operator=(const AlarmList&) = delete;

	AlarmList(AlarmList&&) = default;
	AlarmList& operator=(AlarmList&&) = default;

	using std::vector<Alarm>::size;
	using std::vector<Alarm>::reserve;
	using std::vector<Alarm>::begin;
	using std::vector<Alarm>::end;

	void add(Alarm a)
	{
		push_back(std::move(a));
	}

	void emplace(Alarm::Type t)
	{
		emplace_back(std::forward<Alarm::Type>(t));
	}
};
}
