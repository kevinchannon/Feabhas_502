#pragma once

#include "String.hpp"

#include <random>

namespace kjc
{
	class Alarm
	{
	public:
		enum class Type
		{
			Unknown = -1,

			Warning,
			Caution,
			Advisory,

			TypeCount
		};

		[[nodiscard]] static const wchar_t* type_to_string(Type t);
		[[nodiscard]] static constexpr bool type_is_valid(Type t);

		explicit Alarm(Type t) noexcept;
		Alarm(Type t, String description) noexcept;
		Alarm() noexcept;

		Alarm(const Alarm&) noexcept = default;
		Alarm(Alarm&&) noexcept = default;

		~Alarm() noexcept = default;

		Alarm& operator=(const Alarm& other) noexcept = default;
		Alarm& operator=(Alarm&& other) noexcept = default;

		bool operator==(const Alarm& other) const noexcept;
		bool operator!=(const Alarm& other) const noexcept;

		[[nodiscard]] Type type() const noexcept;

		[[nodiscard]] const wchar_t* as_string() const;
		[[nodiscard]] const String& description() const;

	private:

		Type _type;
		String _description{};
	};

	[[nodiscard]] Alarm make_alarm(Alarm::Type t);

	[[nodiscard]] Alarm make_random_alarm(std::mt19937_64& rng);
}

