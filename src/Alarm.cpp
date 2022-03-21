#include "Alarm.hpp"

#pragma warning(push)
#pragma warning(disable: 4365)  // warning C4365: 'argument': conversion from 'long' to 'unsigned int', signed/unsigned mismatch
#include <iostream>
#pragma warning(pop)

#include <array>

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
		using LookupEntry_t = std::pair<Type, const char*>;

		const auto index = static_cast<size_t>(t);
		if (index > static_cast<size_t>(Type::TypeCount)) {
			return _type_to_string(Type::Unknown);
		}

		static constexpr auto name_lookup = std::array{
			LookupEntry_t{Type::Warning, "Warning"},
			LookupEntry_t{Type::Caution, "Caution"},
			LookupEntry_t{Type::Advisory, "Advisory"}
		};

		static_assert(Type::TypeCount == Type(3), "Invalid type count. Check array above");

		return name_lookup[index].second;
	}
}
