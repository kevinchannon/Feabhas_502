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


#include "AlarmPipe.hpp"
#include "Generator.hpp"
#include "Display.hpp"
#include "Pipeline.hpp"

///////////////////////////////////////////////////////////////////////////////

template<typename Fn_T>
void repeat(Fn_T fn, size_t count)
{
	while (count--) {
		fn();
	}
}

///////////////////////////////////////////////////////////////////////////////

int main()
{
	spdlog::set_level(spdlog::level::info);

	std::mt19937_64 rng{ 2123134 }; // Arbitrary seed.

	try {
		auto pipe = kjc::AlarmPipe{};
		auto generator = kjc::Generator{ pipe , rng };
		auto display = kjc::Display{ pipe, std::wcout };
		auto pipeline = kjc::Pipeline{};

		pipeline.add(generator);
		pipeline.add(display);

		repeat([&pipeline]() { pipeline.run(); }, 10);
	}
	catch (const kjc::PipeException& ex) {
		spdlog::error("Pipe failure: {}", ex.what());
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
