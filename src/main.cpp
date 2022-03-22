// -----------------------------------------------------------------------------
// main program
//
// DISCLAIMER:
// Feabhas is furnishing this item "as is". Feabhas does not provide any
// warranty of the item whatsoever, whether express, implied, or statutory,
// including, but not limited to, any warranty of merchantability or fitness
// for a particular purpose or any warranty that the contents of the item will
// be error-free.
// In no respect shall Feabhas incur any liability for any damages, including,
// but limited to, direct, indirect, special, or consequential damages arising
// out of, resulting from, or any way connected to the use of the item, whether
// or not based upon warranty, contract, tort, or otherwise; whether or not
// injury was sustained by persons or property or otherwise; and whether or not
// loss was sustained from, or arose out of, the results of, the item, or any
// services that may be provided by Feabhas.
// -----------------------------------------------------------------------------


#include "Alarm.hpp"
#include "AlarmIO.hpp"
#include "AlarmPipe.hpp"

#pragma warning(push)
#pragma warning(disable: 4710)	// warning C4710: function not inlined
void wait()
{
    int x;
    std::cin >> x;
}
#pragma warning(pop)

int main()
{
    spdlog::set_level(spdlog::level::debug);
    try {

spdlog::info("Creating an alarm");

        const auto alarm = kjc::Alarm{ kjc::Alarm::Type::Advisory };

spdlog::info("Creating a pipe");

        auto pipe = kjc::AlarmPipe<20>{};

spdlog::info("Pushing something into pipe");

        pipe.push(make_alarm(kjc::Alarm::Type::Caution));

spdlog::info("Pulling from pipe");

        const auto alarm_from_pipe = pipe.pull();

spdlog::info("Results:");

        std::cout << "Alarm: " << alarm << std::endl;
        std::cout << "Alarm from pipe: " << alarm_from_pipe << std::endl;
    }
    catch (const kjc::PipeException& ex) {
        spdlog::error("Pipe failure: {}", ex.what());
    }

spdlog::info("Waiting for exit");

    wait();
    return 0;
}
