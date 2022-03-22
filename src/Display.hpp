#pragma once

#include "Filter.hpp"

namespace kjc
{
	class AlarmPipe;
	class Alarm;

	class Display : public Filter
	{
	public:
		Display(AlarmPipe& pipe, std::ostream& os);

		void execute() override;

	private:

		static const char* _get_alarm_string(const std::optional<Alarm>& a);

		AlarmPipe& _pipe;
		std::ostream& _os;
	};
}
