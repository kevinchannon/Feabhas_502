#pragma once

#include "Filter.hpp"

#include <random>

namespace kjc
{
	class AlarmPipe;

	class Generator : public Filter
	{
	public:
		Generator(AlarmPipe& pipe, std::mt19937_64& rng, size_t how_many);

		Generator(const Generator&) = delete;
		Generator(Generator&&) = delete;
		Generator& operator=(const Generator&) = delete;
		Generator& operator=(Generator&&) = delete;

		void execute() override;

	private:
		std::mt19937_64& _rng;
		AlarmPipe& _pipe;
		size_t _how_many;
	};

}
