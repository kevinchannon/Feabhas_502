#pragma once

#include "Alarm.hpp"

#include <vector>

namespace kjc
{
class AlarmList
{
public:
	AlarmList() noexcept = default;

	AlarmList(const AlarmList&) = delete;
	AlarmList& operator=(const AlarmList&) = delete;

	AlarmList(AlarmList&&) = default;
	AlarmList& operator=(AlarmList&&) = default;

	[[nodiscard]] size_t size() const noexcept { return _alarms.size(); }

	void add(Alarm a)
	{
		_alarms.push_back(std::move(a));
	}

	void emplace(Alarm::Type t)
	{
		_alarms.emplace_back(std::forward<Alarm::Type>(t));
	}

	void reserve(size_t how_many)
	{
		_alarms.reserve(how_many);
	}

	auto begin() const { return _alarms.cbegin(); }
	auto begin() { return _alarms.begin(); }

	auto end() const { return _alarms.cend(); }
	auto end() { return _alarms.cend(); }

private:
	std::vector<Alarm> _alarms;
};
}
