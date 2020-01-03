#pragma once

#ifdef BLUE
    #undef BLUE
#endif

#ifdef RED
    #undef RED
#endif

#ifdef GREEN
    #undef GREEN
#endif

#ifdef YELLOW
    #undef YELLOW
#endif

enum class PlayerColor {
    BLUE = 0,
    RED,
    GREEN,
    YELLOW
};