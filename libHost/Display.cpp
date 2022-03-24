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
		const auto alarms = _pipe.pull();
		if (alarms.size() == 0) {
			return;
		}

		for (auto alarm : alarms | std::views::take(alarms.size() - 1) ) {
			_os << _get_alarm_string(alarm) << ',';
		}

		_os << _get_alarm_string(*std::prev(alarms.end()));
	}

	const wchar_t* Display::_get_alarm_string(const std::optional<Alarm>& a)
	{
		return a ? a->as_string() : L"NO ALARM";
	}
}