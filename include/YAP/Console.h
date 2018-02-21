#pragma once

#include <iostream>

namespace YAP {

namespace Colors {

#define DEFINE_COLOR(name, special_str)        \
inline std::ostream &name(std::ostream &os) {  \
    return os << (special_str);                \
}

DEFINE_COLOR(reset, "\x1B[00m")

DEFINE_COLOR(bold, "\x1B[01m")
DEFINE_COLOR(italic, "\x1B[03m")
DEFINE_COLOR(underlined, "\x1B[04m")

DEFINE_COLOR(white, "\x1B[37m")
DEFINE_COLOR(red, "\x1B[31m")
DEFINE_COLOR(green, "\x1B[32m")
DEFINE_COLOR(yellow, "\x1B[33m")
DEFINE_COLOR(blue, "\x1B[34m")
DEFINE_COLOR(magenta, "\x1B[35m")
DEFINE_COLOR(cyan, "\x1B[36m")
DEFINE_COLOR(grey, "\x1B[02m")
DEFINE_COLOR(darkgrey, "\x1B[30m")

DEFINE_COLOR(white_bckg, "\x1B[07m")
DEFINE_COLOR(red_bckg, "\x1B[41m")
DEFINE_COLOR(green_bckg, "\x1B[42m")
DEFINE_COLOR(yellow_bckg, "\x1B[43m")
DEFINE_COLOR(blue_bckg, "\x1B[44m")
DEFINE_COLOR(magenta_bckg, "\x1B[45m")
DEFINE_COLOR(cyan_bckg, "\x1B[46m")
DEFINE_COLOR(grey_bckg, "\x1B[47m")
DEFINE_COLOR(darkgrey_bckg, "\x1B[40m")

} // namespace Colors

} // namespace YAP
