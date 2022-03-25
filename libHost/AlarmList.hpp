#pragma once

#include "Alarm.hpp"
#include "String.hpp"

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

	void add(Alarm a);

	template<typename... Args_T>
	void emplace(Args_T&&... args)
	{
		emplace_back(std::forward<Args_T>(args)...);
	}
	
	void erase(Alarm::Type t);
};

AlarmList make_random_alarm_list(size_t how_many, std::mt19937_64& rng);

}
