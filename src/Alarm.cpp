#include "Alarm.hpp"

namespace kjc
{
	Alarm::Alarm() : _type{ Type::Unknown }
	{
	}

	Alarm::Alarm(Type t) : _type{ t }
	{
	}

	Alarm::~Alarm()
	{
	}

	Alarm::Type Alarm::type() const
	{
		return _type;
	}

	const char* Alarm::as_string() const
	{
		return _type_to_string(_type);
	}
	
	const char* Alarm::_type_to_string(Type t)
	{
		switch (t)
		{
		case Type::Warning: {
			return "Warning";
		}

		case Type::Caution: {
			return "Caution";
		}

		case Type::Advisory: {
			return "Advisory";
		}

		case Type::Unknown: {
			return "Unknown";
		}

		default:;
		}

		return "Unknown";
	}
}
