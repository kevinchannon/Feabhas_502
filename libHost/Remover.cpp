#include "Remover.hpp"

#include "AlarmPipe.hpp"

namespace kjc
{

	Remover::Remover(AlarmPipe& ingress, AlarmPipe& egress, Alarm::Type to_remove) noexcept
		: _ingress{ ingress }
		, _egress{ egress }
		, _to_remove{ to_remove }
	{}

	void Remover::execute()
	{
		auto alarms = _ingress.pull();
		alarms.erase(std::remove_if(alarms.begin(), alarms.end(), [this](auto&& alarm) { return _to_remove == alarm.type(); }));
		_egress.push(std::move(alarms));
	}

}
