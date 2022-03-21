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
		Alarm(Type t);

		~Alarm();

		Alarm& operator=(const Alarm&) = delete;

		Type type() const;

		const char* as_string() const;

	private:

		static const char* _type_to_string(Type t);

		const Type _type;
	};
}

