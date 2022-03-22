#include "Display.hpp"

#include "AlarmPipe.hpp"

namespace kjc
{
	Display::Display(AlarmPipe& pipe, std::ostream& os)
		: _pipe{ pipe }
		, _os{ os }
	{}

	void Display::execute()
	{
		_os << _get_alarm_string(_pipe.pull()) << '\n';
	}

	const char* Display::_get_alarm_string(const std::optional<Alarm>& a)
	{
		return a ? a->as_string() : "NO ALARM";
	}
}