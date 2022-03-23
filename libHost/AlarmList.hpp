#pragma once

#include "Alarm.hpp"

#include <vector>

namespace kjc
{
class AlarmList
{
public:
	AlarmList() noexcept = default;

	[[nodiscard]] size_t size() const noexcept { return _alarms.size(); }

	void add(Alarm a)
	{
		_alarms.push_back(std::move(a));
	}

private:
	std::vector<Alarm> _alarms;
};
}
