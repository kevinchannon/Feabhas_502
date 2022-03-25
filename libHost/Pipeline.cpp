#include "Pipeline.hpp"

#include "Filter.hpp"

namespace kjc
{
	Pipeline::Pipeline(std::initializer_list<Filter*> filters)
		: _filters{ filters }
	{}

	void Pipeline::add(Filter& f)
	{
		_filters.push_back(&f);
	}

	void Pipeline::run()
	{
		std::ranges::for_each(_filters, [](auto&& f) { f->execute(); });
	}
}
