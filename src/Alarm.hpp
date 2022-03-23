#pragma once

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

		Alarm() noexcept;
		explicit Alarm(Type t) noexcept;
		Alarm(const Alarm& other) noexcept;
		Alarm(Alarm&& other) noexcept;

		~Alarm() noexcept;

		Alarm& operator=(const Alarm& other) noexcept;
		Alarm& operator=(Alarm&& other) noexcept;

		[[nodiscard]] Type type() const noexcept;

		[[nodiscard]] const char* as_string() const;

	private:

		[[nodiscard]] static const char* _type_to_string(Type t);

		Type _type;
	};

	[[nodiscard]] Alarm make_alarm(Alarm::Type t);

	[[nodiscard]] Alarm make_random_alarm(std::mt19937_64& rng);
}

