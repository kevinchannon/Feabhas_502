#include "Remover.hpp"

#include "AlarmPipe.hpp"

namespace kjc
{
	Remover::Remover(AlarmPipe& ingress, AlarmPipe& egress, Alarm::Type to_remove) noexcept
		: _to_remove{ to_remove }
		, _ingress{ ingress }
		, _egress{ egress }
	{}

	void Remover::execute()
	{
		auto alarms = _ingress.pull();
		alarms.erase(_to_remove);
		_egress.push(std::move(alarms));
	}
}
