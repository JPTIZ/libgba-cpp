#ifndef GBA_DRIVERS_DISPLAY_OBJ_H
#define GBA_DRIVERS_DISPLAY_OBJ_H

#include <libgba-cpp/arch/display/video.h>

namespace gba::display {

/**
 * Object mapping mode.
 */
enum class ObjectMapping {
    /**
     * Object data as unidimensional array.
     */
    MAP_ARRAY,

    /**
     * Object data as tile matrix.
     */
    MAP_TILE_MATRIX,
};


/**
 * Object Color Palette array.
 */
RawPalette<256>& obj_palette();


/**
 * Changes object mapping mode.
 */
inline void object_mapping(ObjectMapping map) {
    gba::arch::registers::display::lcd_control[6] = utils::value_of(map);
}

}

#endif
