/** Color.h
 *  Provides an enum of 4-bit VGA color, as well as functions to easily produce their Virtual
 *  Terminal Escape Sequences.
 */

#pragma once

#include <string>
#include <cstdint>

enum class Color : uint8_t {
    Black = 0,
    DarkRed,
    DarkGreen,
    DarkYellow,
    DarkBlue,
    DarkMagenta,
    DarkCyan,
    LightGray,
    DarkGray,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Transparent
};

// Produce the Virtual Terminal Escape Sequence for setting the foreground color
const std::string color_esc_fg(Color color);

// Produce the Virtual Terminal Escape Sequence for setting the background color
const std::string color_esc_bg(Color color);
