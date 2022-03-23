
#include <Alarm.hpp>

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<>
std::wstring __cdecl Microsoft::VisualStudio::CppUnitTestFramework::ToString<enum kjc::Alarm::Type>(const enum kjc::Alarm::Type& t)
{
	return kjc::Alarm::type_to_string(t);
}

namespace testHost
{
	using namespace kjc;

	TEST_CLASS(TestAlarm)
	{
	public:

		TEST_METHOD(IsDefaultConstructedAsUnknownType)
		{
			Assert::AreEqual(Alarm::Type::Unknown, Alarm{}.type());
		}
		
		TEST_METHOD(ConstructWithValueReturnsCorrectType)
		{
			Assert::AreEqual(Alarm::Type::Advisory, Alarm{ Alarm::Type::Advisory }.type());
			Assert::AreEqual(Alarm::Type::Caution, Alarm{ Alarm::Type::Caution }.type());
			Assert::AreEqual(Alarm::Type::Warning, Alarm{ Alarm::Type::Warning }.type());
		}

		TEST_METHOD(AsStringReturnsTheCorrectString)
		{
			Assert::AreEqual(L"Advisory", Alarm{ Alarm::Type::Advisory }.as_string());
			Assert::AreEqual(L"Caution", Alarm{ Alarm::Type::Caution }.as_string());
			Assert::AreEqual(L"Warning", Alarm{ Alarm::Type::Warning }.as_string());
		}
	};
}
