#include "Display.hpp"

#include "AlarmPipe.hpp"

namespace kjc
{
	Display::Display(AlarmPipe& pipe, std::wostream& os)
		: _pipe{ pipe }
		, _os{ os }
	{}

	void Display::execute()
	{
		_os << _get_alarm_string(_pipe.pull()) << '\n';
	}

	const wchar_t* Display::_get_alarm_string(const std::optional<Alarm>& a)
	{
		return a ? a->as_string() : L"NO ALARM";
	}
}