
#include <Alarm.hpp>
#include <Pipe.hpp>
#include <Generator.hpp>
#include <AlarmPipe.hpp>
#include <AlarmList.hpp>

#include <Repeat.hpp>

#include "CppUnitTest.h"

#include <random>

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

		TEST_METHOD(AnInvalidTypeReportsCorrectString)
		{
			Assert::AreEqual(L"Invalid", Alarm{ static_cast<Alarm::Type>(static_cast<int>(Alarm::Type::TypeCount) + 1)}.as_string());
			Assert::AreEqual(L"Invalid", Alarm{ static_cast<Alarm::Type>(-2) }.as_string());
		}
	};

	TEST_CLASS(TestAlarmList)
	{
	public:
		TEST_METHOD(AddingAlarmsWorks)
		{
			std::mt19937_64 rng{ 98324 };

			auto alarms = AlarmList{};
			kjc::repeat([&alarms, &rng]() { alarms.add(make_random_alarm(rng)); }, 10);

			Assert::AreEqual(size_t{ 10 }, alarms.size());
		}

		TEST_METHOD(EmplacingAlarmsWorks)
		{
			std::mt19937_64 rng{ 98324 };

			auto alarms = AlarmList{};
			kjc::repeat([&alarms, &rng]() { alarms.emplace(make_random_alarm(rng).type()); }, 10);

			Assert::AreEqual(size_t{ 10 }, alarms.size());
		}
	};

	TEST_CLASS(TestPipe)
	{
	public:
		TEST_METHOD(IsEmptyOnConstruction)
		{
			Assert::IsTrue(Pipe<int, 10>{}.is_empty());
		}

		TEST_METHOD(IsNotFullOnConstruction)
		{
			Assert::IsFalse(Pipe<int, 10>{}.is_full());
		}

		TEST_METHOD(IsFullReportsTrueWhenPipeIsFull)
		{
			constexpr auto pipe_capacity = 4;

			auto pipe = Pipe<int, pipe_capacity>{};
			for (auto i = 0u; i < pipe_capacity; ++i) {
				Assert::IsFalse(pipe.is_full());
				pipe.push(i);
			}

			Assert::IsTrue(pipe.is_full());
		}

		TEST_METHOD(ItemsAreHandledFIFO)
		{
			constexpr auto pipe_capacity = 20;

			auto pipe = Pipe<unsigned, pipe_capacity>{};
			for (auto i = 0u; i < pipe_capacity; ++i) {
				pipe.push(i);
			}

			for (auto i = 0u; i < pipe_capacity; ++i) {
				Assert::AreEqual(i, pipe.pull());
			}
		}

		TEST_METHOD(ExceptionOccursWhenPullingFromAnEmptyPipe)
		{
			Assert::ExpectException<PipeEmpty>([]() { std::ignore = Pipe<int, 10>{}.pull(); });
		}

		TEST_METHOD(ExceptionOccursWhenPushingToAFullPipe)
		{
			auto pipe = Pipe<int, 1>{};
			pipe.push(1);

			Assert::ExpectException<PipeFull>([&pipe]() { pipe.push(0); });
		}

		TEST_METHOD(TryPullReturnsNullIfPipeIsEmpty)
		{
			Assert::IsTrue(std::nullopt == Pipe<double, 10>{}.try_pull());
		}

		TEST_METHOD(TryPushReturnsFalseIfPipeIsFull)
		{
			auto pipe = Pipe<int, 1>{};
			pipe.push(1);

			Assert::IsFalse(pipe.try_push(10));
		}

		TEST_METHOD(ZeroSizePipeIsAlwaysBothFullAndEmpty)
		{
			auto pipe = Pipe<int, 0>{};
			Assert::IsTrue(pipe.is_full());
			Assert::IsTrue(pipe.is_empty());
		}

		TEST_METHOD(ReturnsToEmptyWhenAllItemsArePulled)
		{
			constexpr auto pipe_capacity = 20;

			auto pipe = Pipe<unsigned, pipe_capacity>{};
			for (auto i = 0u; i < pipe_capacity; ++i) {
				pipe.push(i);
			}

			for (auto i = 0u; i < pipe_capacity; ++i) {
				std::ignore = pipe.pull();
			}

			Assert::IsTrue(pipe.is_empty());
		}

		TEST_METHOD(NumberOfPushesExceedsCapacityIsOK)
		{
			auto pipe = Pipe<unsigned, 10>{};

			const auto fill_and_empty_pipe = [&pipe]() {
				Assert::IsTrue(pipe.is_empty());
				Assert::IsFalse(pipe.is_full());

				for (auto i = 0u; i < 10; ++i) {
					pipe.push(i);
				}

				Assert::IsTrue(pipe.is_full());

				for (auto i = 0u; i < 10; ++i) {
					std::ignore = pipe.pull();
				}

				Assert::IsTrue(pipe.is_empty());
				Assert::IsFalse(pipe.is_full());
			};

			kjc::repeat(fill_and_empty_pipe, 1'000'000);
		}
	};
}
