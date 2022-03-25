#pragma once

#include <variant>
#include <array>

namespace kjc
{

	class String
	{
	public:
		String(const wchar_t* s);

		String() = default;
		~String() = default;
		String(const String& other) = default;
		String(String&& other) = default;

		String& operator=(const String& other) = default;
		String& operator=(String&& other) = default;

		[[nodiscard]] const wchar_t* what() const noexcept { return _store.what(); }
		[[nodiscard]] auto length() const noexcept { return _store.length(); }

	private:

		class dynamic_str
		{
		public:
			dynamic_str() = delete;
			~dynamic_str();
			dynamic_str(const wchar_t* s, size_t len);
			dynamic_str(const dynamic_str& other);
			dynamic_str(dynamic_str&& other) noexcept;
			dynamic_str& operator=(dynamic_str other)
			{
				swap(*this, other);
				return *this;
			}

			friend void swap(dynamic_str& a, dynamic_str& b) noexcept
			{
				using std::swap;

				swap(a.len, b.len);
				swap(a.data, b.data);
			}

			size_t len{ 0 };
			wchar_t* data{nullptr};
		};

		static constexpr auto max_static_str_len = (sizeof(dynamic_str) - sizeof(uint8_t) - sizeof(L'\0')) / sizeof(L'\0');
		class static_str
		{
		public:
			static_str() = default;
			static_str(const wchar_t* s, size_t len);
			static_str(const static_str&) noexcept = default;
			static_str(static_str&&) noexcept = default;
			static_str& operator=(const static_str&) noexcept = default;
			static_str& operator=(static_str&&) noexcept = default;

			uint8_t len{ 0 };
			std::array<wchar_t, max_static_str_len + 1> data{};
		};

		class Storage : protected std::variant<dynamic_str, static_str>
		{
		public:
			using Base_t = std::variant<dynamic_str, static_str>;

			Storage();
			Storage(static_str s);
			Storage(dynamic_str s);

			size_t length() const noexcept;
			const wchar_t* what() const noexcept;

			Base_t& as_variant();
			const Base_t& as_variant() const;
		};

		static Storage make_store(const wchar_t* s);

		Storage _store;
	};
}