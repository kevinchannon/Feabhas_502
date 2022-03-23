#pragma once

#include "Filter.hpp"

#include <iosfwd>

namespace kjc
{
	class AlarmPipe;
	class Alarm;

	class Display : public Filter
	{
	public:
		Display(AlarmPipe& pipe, std::ostream& os);

		Display(const Display&) = delete;
		Display(Display&&) = delete;
		Display& operator=(const Display&) = delete;
		Display& operator=(Display&&) = delete;

		void execute() override;

	private:

		static const char* _get_alarm_string(const std::optional<Alarm>& a);

		AlarmPipe& _pipe;
		std::ostream& _os;
	};
}
