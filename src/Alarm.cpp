#include "Alarm.hpp"

#pragma warning(push)
#pragma warning(disable: 4365)  // warning C4365: 'argument': conversion from 'long' to 'unsigned int', signed/unsigned mismatch
#include <iostream>
#pragma warning(pop)

namespace kjc
{
	Alarm::Alarm() : _type{ Type::Unknown }
	{
		std::cout << "Alarm default c'tor" << std::endl;
	}

	Alarm::Alarm(Type t) : _type{ t }
	{
		std::cout << "Alarm value c'tor" << std::endl;
	}

	Alarm::~Alarm()
	{
		std::cout << "Alarm default d'tor" << std::endl;
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
