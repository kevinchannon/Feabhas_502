#include "Pipeline.hpp"

#include "Filter.hpp"

namespace kjc
{
	void Pipeline::add(Filter& f)
	{
		_filters.push_back(&f);
	}

	void Pipeline::run()
	{
		std::ranges::for_each(_filters, [](auto&& f) { f->execute(); });
	}
}
