#include "String.hpp"
#include "Overload.hpp"

namespace kjc
{
	String::dynamic_str::~dynamic_str()
	{
		delete[] data;
	}

	String::dynamic_str::dynamic_str(const wchar_t* s, size_t len)
		: len{ len }
		, data{ new wchar_t[len + 1] }
	{
		wcscpy_s(data, len + 1, s);
	}

	String::dynamic_str::dynamic_str(const dynamic_str& other)
		: dynamic_str{other.data, other.len}
	{}

	String::dynamic_str::dynamic_str(dynamic_str&& other) noexcept
		: len{ other.len }
		, data{ std::exchange(other.data, nullptr) }
	{}

	String::static_str::static_str(const wchar_t* s, size_t len)
		: len{ gsl::narrow_cast<uint8_t>(len) }
		, data{}
	{
		std::copy_n(s, len, data.begin());
		data.back() = wchar_t{};
	}

	size_t String::Storage::length() const noexcept
	{
		return std::visit([](auto&& arg) -> size_t { return arg.len; }, this->as_variant());
	}

	const wchar_t* String::Storage::what() const noexcept
	{
		return std::visit(Overload{
			[](const static_str& s) -> const wchar_t* { return s.len > 0 ? s.data.data() : L""; },
			[](const dynamic_str& s) -> const wchar_t* { return s.data ? s.data : L""; }
			}, this->as_variant());
	}

	const String::Storage::Base_t& String::Storage::as_variant() const
	{
		return *this;
	}

	String::Storage::Base_t& String::Storage::as_variant()
	{
		return const_cast<String::Storage::Base_t&>(const_cast<const Storage*>(this)->as_variant());
	}

	String::Storage String::make_store(const wchar_t* s)
	{
		const auto len = wcslen(s);
		return len < max_static_str_len ? Storage{static_str{ s, len }} : Storage{dynamic_str{ s, len }};
	}

	String::Storage::Storage()
		: Base_t{ static_str{} }
	{}

	String::Storage::Storage(static_str s)
		: Base_t{ s }
	{}

	String::Storage::Storage(dynamic_str s)
		: Base_t{ std::move(s) }
	{}

	String::String(const wchar_t* s)
		: _store{ make_store(s) }
	{}
}