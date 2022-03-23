#include "Alarm.hpp"

namespace kjc
{
	Alarm::Alarm() noexcept : _type{ Type::Unknown }
	{
	}

	Alarm::Alarm(Type t) noexcept : _type{ t }
	{
	}

	Alarm::Alarm(const Alarm& other) noexcept
		: _type{ other._type }
	{
	}

	Alarm::Alarm(Alarm&& other) noexcept
		: _type{ other._type }
	{
		other._type = Type::Unknown;
	}

	Alarm::~Alarm() noexcept
	{
	}

	Alarm& Alarm::operator=(const Alarm& other) noexcept
	{
		if (this == &other) {
			return *this;
		}

		_type = other._type;
		return *this;
	}

	Alarm& Alarm::operator=(Alarm&& other) noexcept
	{
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

	const wchar_t* Alarm::as_string() const
	{
		return type_to_string(_type);
	}

	const wchar_t* Alarm::type_to_string(Type t)
	{
		const auto index = static_cast<gsl::index>(t);
		if (index > static_cast<size_t>(Type::TypeCount)) {
			return type_to_string(Type::Unknown);
		}

		static constexpr auto name_lookup = std::array{
			L"Warning",
			L"Caution",
			L"Advisory"
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
		return Alarm{ Alarm::Type{ std::uniform_int_distribution<>{0, static_cast<int>(Alarm::Type::TypeCount) - 1}(rng)} };
	}
}
