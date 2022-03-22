#pragma once

#include "Filter.hpp"

namespace kjc
{
	class AlarmPipe;

	class Generator : public Filter
	{
	public:
		Generator(AlarmPipe& pipe, std::mt19937_64& rng);

		void execute() override;

	private:
		std::mt19937_64& _rng;
		AlarmPipe& _pipe;
	};

}
