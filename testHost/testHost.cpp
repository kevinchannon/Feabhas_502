
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
		
		TEST_METHOD(ConstructWithValueReturnsCorrectType)
		{
			Assert::AreEqual(Alarm::Type::Advisory, Alarm{ Alarm::Type::Advisory }.type());
		}
	};
}
