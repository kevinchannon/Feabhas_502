#include "AlarmList.hpp"
#include "Repeat.hpp"

namespace kjc
{
	void AlarmList::add(Alarm a)
	{
		push_back(std::move(a));
	}

	void AlarmList::emplace(Alarm::Type t)
	{
		emplace_back(std::forward<Alarm::Type>(t));
	}

	void AlarmList::erase(Alarm::Type t)
	{
		std::erase_if(*this, [t](auto&& alarm) { return t == alarm.type(); });
	}

	AlarmList make_random_alarm_list(size_t how_many, std::mt19937_64& rng)
	{
		auto out = AlarmList{};
		kjc::repeat([&out, &rng]() { out.add(make_random_alarm(rng)); }, how_many);
		return out;
	}
}
