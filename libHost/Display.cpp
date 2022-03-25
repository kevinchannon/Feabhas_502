#include "Display.hpp"

#include "AlarmPipe.hpp"

namespace kjc
{
	Display::Display(AlarmPipe& pipe, std::wostream& os)
		: _pipe{ pipe }
		, _os{ os }
	{
		_pipe.set_item_arrived_callback([this]() {
			_have_new_item.notify_all();
			});
	}

	void Display::execute()
	{
		_run_result = std::async(std::launch::async, [this]() { _execute_impl(); });
	}

	void Display::_execute_impl()
	{
		while (_running.load()) {
			std::unique_lock<std::mutex> lock{ _mutex };
			_have_new_item.wait(lock, [this]() {return !_pipe.is_empty(); });

			_pull_and_display();
		}
	}

	void Display::_pull_and_display()
	{
		const auto alarms = _pipe.pull();
		if (alarms.size() == 0) {
			return;
		}

		_display_alarms(alarms);
	}

	void Display::_display_alarms(const AlarmList& alarms)
	{
		for (auto alarm : alarms | std::views::take(alarms.size() - 1)) {
			_os << _get_alarm_string(alarm) << ',';
		}

		_os << _get_alarm_string(*std::prev(alarms.end())) << '\n';
	}

	const wchar_t* Display::_get_alarm_string(const std::optional<Alarm>& a)
	{
		return a ? a->as_string() : L"NO ALARM";
	}
}