#include "Alarm.hpp"

namespace kjc
{
	Alarm::Alarm() : _type{ Type::UNKNOWN }
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
		case Type::WARNING: {
			return "WARNING";
		}

		case Type::CAUTION: {
			return "CAUTION";
		}

		case Type::ADVISORY: {
			return "ADVISORY";
		}

		case Type::UNKNOWN: {
			return "UNKNOWN";
		}

		default:;
		}

		return "UNKNOWN";
	}
}
