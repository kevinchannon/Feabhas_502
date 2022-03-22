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
#include "Generator.hpp"
#include "Display.hpp"

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
    spdlog::set_level(spdlog::level::info);
    try {

        auto pipe = kjc::AlarmPipe{};
        auto generator = kjc::Generator{ pipe };
        auto display = kjc::Display{ pipe, std::cout };

        for (auto i : { 0, 1, 2, 3, 4 }) {
            generator.execute();
            display.execute();
        }
    }
    catch (const kjc::PipeException& ex) {
        spdlog::error("Pipe failure: {}", ex.what());
    }

    wait();
    return 0;
}
