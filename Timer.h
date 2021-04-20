/** Timer.h
 *  Utility class for a simple now() -> double function to be used all over the place for timing,
 *  instead of long and repetitive std::chrono balck magic.
 */

#pragma once

namespace Timer {
	double now();
};
