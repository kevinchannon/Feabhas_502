#include "Alarm.hpp"

namespace kjc
{
	Alarm::Alarm() : _type{ Type::Unknown }
	{
		spdlog::debug("Alarm default c'tor");
	}

	Alarm::Alarm(Type t) : _type{ t }
	{
		spdlog::debug("Alarm value c'tor. _type={}", _type_to_string(_type));
	}

	Alarm::Alarm(const Alarm& other)
		: _type{ other._type }
	{
		spdlog::debug("Alarm copy-constructor. _type={}", _type_to_string(_type));
	}

	Alarm::Alarm(Alarm&& other)
		: _type{ other._type }
	{
		spdlog::debug("Alarm move-constructor. _type={}", _type_to_string(_type));
		other._type = Type::Unknown;
	}

	Alarm::~Alarm()
	{
		spdlog::debug("Alarm d'tor");
	}

	Alarm& Alarm::operator=(const Alarm& other)
	{
		spdlog::debug("Alarm copy-assignment. _type={}, other._type={}", _type_to_string(_type), other._type);
		if (this == &other) {
			return *this;
		}

		_type = other._type;
		return *this;
	}

	Alarm& Alarm::operator=(Alarm&& other)
	{
		spdlog::debug("Alarm move-assignment");
		if (this == &other) {
			return *this;
		}

		_type = other._type;
		other._type = Type::Unknown;
		return *this;
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

	Alarm make_alarm(Alarm::Type t)
	{
		return Alarm{ t };
	}
}
