#pragma once

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

		Alarm();
		explicit Alarm(Type t);
		Alarm(const Alarm& other);
		Alarm(Alarm&& other);

		~Alarm();

		Alarm& operator=(const Alarm& other);

		Alarm& operator=(Alarm&& other);

		[[nodiscard]] Type type() const noexcept;

		const char* as_string() const;

	private:

		static const char* _type_to_string(Type t);

		Type _type;
	};

	Alarm make_alarm(Alarm::Type t);

	Alarm make_random_alarm(std::mt19937_64& rng);
}

