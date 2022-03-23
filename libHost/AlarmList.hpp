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

private:
	std::vector<Alarm> _alarms;
};
}
