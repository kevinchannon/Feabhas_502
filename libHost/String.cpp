#include "String.hpp"

namespace kjc
{
	String::String()
		: _len{ 0 }
		, _s{ nullptr }
	{
	}

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

	String& String::operator=(String other)
	{
		swap(*this, other);
		return *this;
	}

	const wchar_t* String::what() const
	{
		return _s ? _s : L"";
	}

	void swap(String& a, String& b)
	{
		using std::swap;
		swap(a._len, b._len);
		swap(a._s, b._s);
	}
}