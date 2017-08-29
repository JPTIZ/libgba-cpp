#ifndef GBA_DRIVERS_DISPLAY_OBJ_H
#define GBA_DRIVERS_DISPLAY_OBJ_H

#include "control.h"

namespace gba::display {

enum class ObjectMapping {
    MAP_1D,
    MAP_2D,
};

inline void object_mapping(ObjectMapping map) {
    lcd_control[6] = utils::value_of(map);
}

}

#endif
