#pragma once

#include "Alarm.hpp"

#include <vector>
#include <random>

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
	using std::vector<Alarm>::erase;

	void add(Alarm a);
	void emplace(Alarm::Type t);
};

AlarmList make_random_alarm_list(size_t how_many, std::mt19937_64& rng);

}
