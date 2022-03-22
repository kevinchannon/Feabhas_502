#include "Generator.hpp"
#include "Alarm.hpp"
#include "AlarmPipe.hpp"

namespace kjc
{
	void Generator::execute()
	{
		_pipe.push(make_random_alarm(_rng));
	}
}