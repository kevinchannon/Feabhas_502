
#include <Alarm.hpp>
#include <Pipe.hpp>
#include <Generator.hpp>
#include <AlarmPipe.hpp>
#include <AlarmList.hpp>
#include <Display.hpp>
#include <Remover.hpp>
#include <String.hpp>

#include <Repeat.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<>
std::wstring __cdecl Microsoft::VisualStudio::CppUnitTestFramework::ToString<enum kjc::Alarm::Type>(const enum kjc::Alarm::Type& t)
{
	return kjc::Alarm::type_to_string(t);
}

template<>
std::wstring __cdecl Microsoft::VisualStudio::CppUnitTestFramework::ToString<class kjc::Alarm>(const class kjc::Alarm& a)
{
	return a.as_string();
}

namespace testHost
{
	using namespace kjc;

	std::vector<Alarm> make_random_alarms(size_t how_many, uint64_t random_seed)
	{
		std::mt19937_64 rng{ random_seed };

		auto out = std::vector<Alarm>{};
		kjc::repeat([&out, &rng]() { out.push_back(make_random_alarm(rng)); }, how_many);

		return out;
	}

	AlarmList make_random_alarm_list(size_t how_many, uint64_t random_seed)
	{
		std::mt19937_64 rng{ random_seed };

		return kjc::make_random_alarm_list(how_many, rng);
	}

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
			auto random_alarms = make_random_alarms(10, 23408234);
			auto alarms = std::accumulate(random_alarms.begin(), random_alarms.end(), AlarmList{}, [](auto&& alarm_list, auto&& alarm) {
				alarm_list.add(alarm);
				return std::move(alarm_list);
			});

			Assert::AreEqual(size_t{ 10 }, alarms.size());
		}

		TEST_METHOD(EmplacingAlarmsWorks)
		{
			auto random_alarms = make_random_alarms(10, 99023492 );
			auto alarms = std::accumulate(random_alarms.begin(), random_alarms.end(), AlarmList{}, [](auto&& alarm_list, auto&& alarm) {
				alarm_list.emplace(alarm.type());
				return std::move(alarm_list); 
			});

			Assert::AreEqual(size_t{ 10 }, alarms.size());
		}

		TEST_METHOD(BeginPointsToTheFirstAlarm)
		{
			for (auto t : { Alarm::Type::Advisory, Alarm::Type::Caution, Alarm::Type::Warning }) {
				auto alarms = AlarmList{};
				alarms.emplace(t);

				// Add some other alarms to the list, so that we know that there's more than one element in it.
				alarms.emplace(Alarm::Type::Unknown);
				alarms.emplace(Alarm::Type::Unknown);
				alarms.emplace(Alarm::Type::Unknown);

				Assert::AreEqual(Alarm{ t }, *alarms.begin());
			}
		}

		TEST_METHOD(BeginAndEndCanBeUsedToIterateAlarmList)
		{
			const auto alarms = make_random_alarm_list(10, 123 );

			Assert::AreEqual(gsl::narrow_cast<ptrdiff_t>(alarms.size()), std::distance(alarms.begin(), alarms.end()));
		}

		TEST_METHOD(ReserveDoesNotChangeReportedSize)
		{
			auto alarms = AlarmList{};
			alarms.reserve(10);

			Assert::AreEqual(size_t{ 0 }, alarms.size());
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

	TEST_CLASS(TestGenerator)
	{
	public:
		TEST_METHOD(ExecutePushesAlarmsToPipe)
		{
			std::mt19937_64 rng{ 234839432 };
			auto pipe = AlarmPipe{};

			Generator{ pipe, rng }.execute();

			const auto alarms = pipe.pull();

			Assert::IsTrue(alarms.size() > 0);
		}
	};

	TEST_CLASS(TestDisplay)
	{
	public:
		TEST_METHOD(DisplatPrintsAllItemsInAlarmList)
		{
			auto pipe = AlarmPipe{};

			auto alarms = AlarmList{};
			alarms.emplace(Alarm::Type::Advisory);
			alarms.emplace(Alarm::Type::Caution);
			alarms.emplace(Alarm::Type::Warning);

			pipe.push(std::move(alarms));

			std::wstringstream output;
			Display{ pipe, output }.execute();

			Assert::AreEqual(std::wstring(L"Advisory,Caution,Warning\n"), output.str());
		}
	};

	TEST_CLASS(TestRemover)
	{
	public:
		TEST_METHOD(RemovesAlarmsOfTheCorrectType)
		{
			for (auto target_type : {Alarm::Type::Advisory, Alarm::Type::Caution, Alarm::Type::Warning} ) {

				auto in_pipe = AlarmPipe{};
				auto out_pipe = AlarmPipe{};

				auto alarms = AlarmList{};
				alarms.emplace(Alarm::Type::Advisory);
				alarms.emplace(Alarm::Type::Caution);
				alarms.emplace(Alarm::Type::Warning);

				in_pipe.push(std::move(alarms));

				Remover{ in_pipe, out_pipe, target_type }.execute();

				alarms = out_pipe.pull();

				Assert::IsTrue(alarms.end() == std::find(alarms.begin(), alarms.end(), Alarm{ target_type }));
			}
		}
	};

	TEST_CLASS(TestString)
	{
	public:
		TEST_METHOD(DefaultConstructHasZeroLength)
		{
			Assert::AreEqual(size_t{ 0 }, String{}.length());
		}

		TEST_METHOD(DefaultConstructHasEmptyWhat)
		{
			Assert::AreEqual(L"", String{}.what());
		}

		TEST_METHOD(WhatReturnsTheCorrectMessage_long)
		{
			const auto s = String{ L"Hello, String!" };
			Assert::AreEqual(L"Hello, String!", s.what());
		}

		TEST_METHOD(WhatReturnsTheCorrectMessage_short)
		{
			const auto s = String{ L"cat" };
			Assert::AreEqual(L"cat", s.what());
		}

		TEST_METHOD(CopyingStringWorks_long)
		{
			const auto s1 = String{ L"Hello, String!" };
			const String s2{ s1 };

			Assert::AreEqual(s1.what(), s2.what());
		}

		TEST_METHOD(CopyingStringWorks_short)
		{
			const auto s1 = String{ L"dog" };
			const String s2{ s1 };

			Assert::AreEqual(s1.what(), s2.what());
		}

		TEST_METHOD(MoveStringWorks_long)
		{
			constexpr auto expected_str = L"Hello, String!";

			auto s1 = String{ expected_str };
			const String s2{ std::move(s1) };

			Assert::AreEqual(expected_str, s2.what());
			Assert::AreEqual(wcslen(expected_str), s2.length());

			Assert::AreEqual(L"", s1.what());
		}

		TEST_METHOD(MoveStringWorks_short)
		{
			constexpr auto expected_str = L"chick";

			auto s1 = String{ expected_str };
			const String s2{ std::move(s1) };

			Assert::AreEqual(expected_str, s2.what());
			Assert::AreEqual(wcslen(expected_str), s2.length());
		}

		TEST_METHOD(CopyAssignmentWorks_long)
		{
			const auto s1 = String{ L"Hello, String!" };
			auto s2 = String{};

			s2 = s1;

			Assert::AreEqual(s1.what(), s2.what());
			Assert::AreEqual(s1.length(), s2.length());
		}

		TEST_METHOD(CopyAssignmentWorks_short)
		{
			const auto s1 = String{ L"duck" };
			auto s2 = String{};

			s2 = s1;

			Assert::AreEqual(s1.what(), s2.what());
			Assert::AreEqual(s1.length(), s2.length());
		}

		TEST_METHOD(MoveAssignmentWorks_long)
		{
			const auto s1 = String{ L"Hello, String!" };
			auto s2 = String{};

			s2 = std::move(s1);

			Assert::AreEqual(s1.what(), s2.what());
			Assert::AreEqual(s1.length(), s2.length());
		}

		TEST_METHOD(MoveAssignmentWorks_short)
		{
			const auto s1 = String{ L"pig" };
			auto s2 = String{};

			s2 = std::move(s1);

			Assert::AreEqual(s1.what(), s2.what());
			Assert::AreEqual(s1.length(), s2.length());
		}
	};
}
