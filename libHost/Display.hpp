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
		Display(AlarmPipe& pipe, std::wostream& os);

		Display(const Display&) = delete;
		Display(Display&&) = delete;
		Display& operator=(const Display&) = delete;
		Display& operator=(Display&&) = delete;

		void execute() override;

	private:

		static const wchar_t* _get_alarm_string(const std::optional<Alarm>& a);

		AlarmPipe& _pipe;
		std::wostream& _os;
	};
}
