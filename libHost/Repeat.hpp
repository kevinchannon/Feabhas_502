#pragma once

namespace kjc
{
	template<typename Fn_T>
	void repeat(Fn_T fn, size_t count)
	{
		while (count--) {
			std::invoke(fn);
		}
	}
}
