#include "Alarm.hpp"

#include <spdlog/spdlog.h>

#pragma warning(push)
#pragma warning(disable: 4365)  // warning C4365: 'argument': conversion from 'long' to 'unsigned int', signed/unsigned mismatch
#include <iostream>
#pragma warning(pop)

#include <array>

namespace kjc
{
	Alarm::Alarm() : _type{ Type::Unknown }
	{
		spdlog::debug("Alarm default c'tor");
	}

	Alarm::Alarm(Type t) : _type{ t }
	{
		spdlog::debug("Alarm value c'tor");
	}

	Alarm::~Alarm()
	{
		spdlog::debug("Alarm default d'tor");
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
		const auto index = static_cast<size_t>(t);
		if (index > static_cast<size_t>(Type::TypeCount)) {
			return _type_to_string(Type::Unknown);
		}

		static constexpr auto name_lookup = std::array{
			"Warning",
			"Caution",
			"Advisory"
		};

		static_assert(Type::TypeCount == Type(3), "Invalid type count. Check array above");

		return name_lookup[index];
	}
}
