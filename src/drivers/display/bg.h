#ifndef GBA_DRIVERS_DISPLAY_BG_H
#define GBA_DRIVERS_DISPLAY_BG_H

#include "control.h"

namespace gba::display {

enum class Background {
    BG0,
    BG1,
    BG2,
    BG3,
    OBJ,
};

inline void bg_visible(Background bg, bool visible) {
    lcd_control[8 + utils::value_of(bg)] = visible;
}

}

#endif
