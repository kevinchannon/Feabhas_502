#include "String.hpp"

namespace kjc
{
	String::String(const wchar_t* s)
		: _len{ wcslen(s) }
		, _s{ nullptr }
	{
		_s = new wchar_t[_len + 1];
		wcscpy_s(_s, _len + 1, s);
	}

	String::~String()
	{
		delete[] _s;
	}

	String::String(const String& other)
		: String{ other.what() }
	{
	}

	String::String(String&& other)
		: _len{ std::exchange(other._len, 0) }
		, _s{ std::exchange(other._s, nullptr) }
	{
	}

	const wchar_t* String::what() const
	{
		return _s;
	}
}