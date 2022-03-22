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
		const auto alarm = _pipe.try_pull();
		_os << ( alarm ? alarm->as_string() : "NO ALARM") << '\n';
	}
}