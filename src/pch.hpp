#pragma once

#pragma warning(push)
#pragma warning(disable: 4365)  // warning C4365: 'argument': conversion from 'long' to 'unsigned int', signed/unsigned mismatch
#pragma warning(disable: 4820)	// warning C4820: 'N' bytes padding added after data member
#pragma warning(disable: 4625)	// warning C4625: copy constructor was implicitly defined as deleted
#pragma warning(disable: 5027)	// warning C5027: move assignment operator was implicitly defined as deleted
#pragma warning(disable: 4626)  // warning C4626: assignment operator was implicitly defined as deleted
#pragma warning(disable: 5039)	// warning C5039: pointer or reference to potentially throwing function passed to 'extern "C"' function under -EHc. Undefined behavior may occur if this function throws an exception.
#pragma warning(disable: 4623)	// warning C4623: default constructor was implicitly defined as deleted
#pragma warning(disable: 4582)	// warning C4582: constructor is not implicitly called
#pragma warning(disable: 4514)	// warning C4514: unreferenced inline function has been removed
#pragma warning(disable: 4710)	// warning C4710: function not inlined
#pragma warning(disable: 5045)	// warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#include <spdlog/spdlog.h>
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4365)  // warning C4365: 'argument': conversion from 'long' to 'unsigned int', signed/unsigned mismatch

#ifndef _DEBUG
#pragma warning(disable: 4710)	// warning C4710: function not inlined
#pragma warning(disable: 4711)	// warning C4711: selected for automatic inline expansion
#endif

#include <iostream>
#pragma warning(pop)

#include <stdexcept>
#include <string_view>
#include <optional>


#include <array>