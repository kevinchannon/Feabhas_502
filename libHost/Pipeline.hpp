#pragma once

namespace kjc
{
	class Filter;

	class Pipeline
	{
	public:
		Pipeline() = default;

		Pipeline(const Pipeline&) = delete;
		Pipeline(Pipeline&&) = delete;

		Pipeline& operator=(const Pipeline&) = delete;
		Pipeline& operator=(Pipeline&&) = delete;

		void add(Filter& f);

		void run();

	private:
		std::vector<Filter*> _filters;
	};
}
