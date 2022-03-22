#pragma once

#include "Filter.hpp"

namespace kjc
{
	class AlarmPipe;

	class Display : public Filter
	{
	public:
		Display(AlarmPipe& pipe, std::ostream& os);

		void execute() override;

	private:
		AlarmPipe& _pipe;
		std::ostream& _os;
	};
}
