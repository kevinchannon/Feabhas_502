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

	Alarm::Type Alarm::type() const noexcept
	{
		return _type;
	}

	const char* Alarm::as_string() const
	{
		return _type_to_string(_type);
	}
	
	const char* Alarm::_type_to_string(Type t)
	{
		const auto index = static_cast<gsl::index>(t);
		if (index > static_cast<size_t>(Type::TypeCount)) {
			return _type_to_string(Type::Unknown);
		}

		static constexpr auto name_lookup = std::array{
			"Warning",
			"Caution",
			"Advisory"
		};

		static_assert(Type::TypeCount == Type(3), "Invalid type count. Check array above");

		return gsl::at(name_lookup, index);
	}

	Alarm make_alarm(Alarm::Type t)
	{
		return Alarm{ t };
	}

	Alarm make_random_alarm(std::mt19937_64& rng)
	{
		return Alarm{ Alarm::Type(std::uniform_int_distribution<>{0,2}(rng)) };
	}
}
