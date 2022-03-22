#include "Generator.hpp"
#include "Alarm.hpp"
#include "AlarmPipe.hpp"

namespace kjc
{
	Generator::Generator(AlarmPipe& pipe, std::mt19937_64& rng)
		: _rng{ rng }	// Arbitrary seed.
		, _pipe{ pipe }
	{}

	void Generator::execute()
	{
		_pipe.push(make_random_alarm(_rng));
	}
}