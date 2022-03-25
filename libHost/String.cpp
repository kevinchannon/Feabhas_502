#include "String.hpp"

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
	{
	}

	String::dynamic_str::dynamic_str(dynamic_str&& other) noexcept
		: len{ other.len }
		, data{ std::exchange(other.data, nullptr) }
	{

	}

	String::static_str::static_str(const wchar_t* s, size_t len)
		: len{ gsl::narrow_cast<uint8_t>(len) }
	{
		std::copy_n(s, len, data.begin());
		data.back() = wchar_t{};
	}

	size_t String::Storage::length() const noexcept
	{
		return std::visit([](auto&& arg) -> size_t { return arg.len; }, *this);
	}

	const wchar_t* String::Storage::what() const noexcept
	{
		return std::visit([](auto&& arg) -> const wchar_t* {
				using Arg_t = std::decay_t<decltype(arg)>;
				if constexpr (std::is_same_v<Arg_t, static_str>) {
					return arg.len > 0 ? arg.data.data() : L"";
				}
				else {
					return arg.len > 0 ? arg.data : L"";
				}
			}, * this);
	}

	String::Storage String::make_store(const wchar_t* s)
	{
		const auto len = wcslen(s);
		if (len < max_static_str_len) {
			return { static_str{s, len} };
		}
		else {
			return { dynamic_str{s, len} };
		}
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
	{
	}
}