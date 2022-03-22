#pragma once

namespace kjc
{
	class Filter
	{
	public :
		virtual ~Filter() noexcept {}

		virtual void execute() = 0;
	};
}
