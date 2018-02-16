#pragma once

#include <iostream>

namespace State {
    enum Id : std::size_t {
        S0,
        S1,
        S2,
        S3,
        S4,
        S5,
        S6,
        S7,
        S8,
        S9,
        NB_STATES
    };

#define TRIVIAL_NAME(name) [name]=#name

    constexpr const char *Names[] = {
            [S0]="Init",
            TRIVIAL_NAME(S1),
            TRIVIAL_NAME(S2),
            TRIVIAL_NAME(S3),
            TRIVIAL_NAME(S4),
            TRIVIAL_NAME(S5),
            TRIVIAL_NAME(S6),
            TRIVIAL_NAME(S7),
            TRIVIAL_NAME(S8),
            TRIVIAL_NAME(S9),
            [NB_STATES]="ERROR",
    };

#undef TRIVIAL_NAME

    inline std::ostream &operator<<(std::ostream &os, const Id &state) {
        os << Names[state];
        return os;
    }
}
