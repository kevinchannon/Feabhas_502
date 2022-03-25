#pragma once

#include "Filter.hpp"

#include <iosfwd>
#include <future>
#include <mutex>

namespace kjc
{
	class AlarmPipe;
	class Alarm;
	class AlarmList;

	class Display : public Filter
	{
	public:
		Display(AlarmPipe& pipe, std::wostream& os);

		Display(const Display&) = delete;
		Display(Display&&) = delete;
		Display& operator=(const Display&) = delete;
		Display& operator=(Display&&) = delete;

		void execute() override;

	private:

		void _execute_impl();
		void _pull_and_display();
		void _display_alarms(const AlarmList& alarms);

		static const wchar_t* _get_alarm_string(const std::optional<Alarm>& a);

		AlarmPipe& _pipe;
		std::wostream& _os;
		std::future<void> _run_result;
		std::condition_variable _have_new_item;
		std::mutex _mutex;
		std::atomic<bool> _running;
	};
}
