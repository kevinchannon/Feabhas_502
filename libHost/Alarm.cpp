#include "Alarm.hpp"

namespace kjc
{
	Alarm::Alarm() noexcept : _type{ Type::Unknown }
	{
	}

	Alarm::Alarm(Type t) noexcept
		: _type{ t }
	{
	}

	Alarm::Alarm(Type t, String description) noexcept
		: _type{ t }
		, _description{ std::move(description) }
	{
	}

	bool Alarm::operator==(const Alarm& other) const noexcept
	{
		return _type == other.type();
	}

	bool Alarm::operator!=(const Alarm& other) const noexcept
	{
		return !(*this == other);
	}

	Alarm::Type Alarm::type() const noexcept
	{
		return _type;
	}

	const wchar_t* Alarm::as_string() const
	{
		return type_to_string(_type);
	}

	const String& Alarm::description() const
	{
		return _description;
	}

	const wchar_t* Alarm::type_to_string(Type t)
	{
		if (!type_is_valid(t)) {
			return L"Invalid";
		}

		static constexpr auto name_lookup = std::array{
			L"Unknown",
			L"Warning",
			L"Caution",
			L"Advisory"
		};

		static_assert(Type::TypeCount == Type(3), "Invalid type count. Check array above");

		return gsl::at(name_lookup, 1 + static_cast<gsl::index>(t));
	}

	constexpr bool Alarm::type_is_valid(Type t)
	{
		return static_cast<gsl::index>(t) < static_cast<gsl::index>(Type::TypeCount) && static_cast<gsl::index>(t) >= -1;
	}

	Alarm make_alarm(Alarm::Type t)
	{
		static const auto descriptions = std::map<Alarm::Type, String>{
			{Alarm::Type::Advisory, L"This is an advisory alarm. Can be ignored safely, but something is not quite right" },
			{Alarm::Type::Caution, L"Take care!"},
			{Alarm::Type::Warning, L"Warn!"}
		};

		return Alarm{ t, descriptions.at(t) };
	}

	Alarm make_random_alarm(std::mt19937_64& rng)
	{
		return make_alarm( Alarm::Type{ std::uniform_int_distribution<>{0, static_cast<int>(Alarm::Type::TypeCount) - 1}(rng)} );
	}
}
