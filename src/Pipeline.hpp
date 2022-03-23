#pragma once

namespace kjc
{
	class Filter;

	class Pipeline
	{
	public:
		Pipeline() = default;

		void add(Filter& f);

		void run();

	private:
		std::vector<Filter*> _filters;
	};
}
