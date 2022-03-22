#pragma once

namespace kjc
{
	class Filter
	{
	public :
		virtual ~Filter() = default;

		virtual void execute() = 0;
	};
}
