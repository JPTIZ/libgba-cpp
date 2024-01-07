#ifndef GBA_DRIVERS_DISPLAY_OBJ_H
#define GBA_DRIVERS_DISPLAY_OBJ_H

#include <libgba-cpp/arch/display/tilemap.h>
#include <libgba-cpp/arch/display/video.h>
#include <libgba-cpp/utils/bitset.h>

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
auto obj_palette() -> RawPalette<256>&;

/**
 * Changes object mapping mode.
 */
inline void object_mapping(ObjectMapping map) {
    gba::arch::registers::display::lcd_control[6] = utils::value_of(map);
}

enum class ObjectMode {
    NORMAL,
    SEMI_TRANSPARENT,
    OBJECT_WINDOW,
};

enum class ObjectColorMode {
    COLORS_16,
    COLORS_256,
};

enum class ObjectShape {
    SQUARE,
    HORIZONTAL,
    VERTICAL,
};

enum class ObjectSize {
    TINY,
    SMALL,
    MEDIUM,
    BIG,
};

enum class ObjectPriority {
    HIGHEST,
    HIGH,
    LOW,
    LOWEST,
};

struct OAMEntry {
    gba::utils::bitset<uint16_t> attr0;
    gba::utils::bitset<uint16_t> attr1;
    gba::utils::bitset<uint16_t> attr2;
    uint16_t _unused;

    auto set_x(int y) -> void {
        attr1 = (attr1.to_ulong() & ~0b11111111) | (y & 0b11111111);
    }

    auto set_y(int y) -> void {
        attr0 = (attr0.to_ulong() & ~0b11111111) | (y & 0b11111111);
    }

    auto rotation_scaling(bool enabled) -> void {
        attr0[8] = enabled;
    }

    auto visible(bool visible) -> void {
        attr0[9] = not visible;
    }

    auto mode(ObjectMode mode) -> void {
        attr0 = (attr0.to_ulong() & ~0b110000000000) |
                (utils::value_of(mode) << 10);
    }

    auto mosaic(bool enabled) -> void {
        attr0[12] = enabled;
    }

    auto color_mode(ObjectColorMode mode) -> void {
        attr0[13] = utils::value_of(mode);
    }

    auto shape(ObjectShape shape) -> void {
        attr0 = (attr0.to_ulong() & 0b0011111111111111) |
                (utils::value_of(shape) << 14);
    }

    auto size(ObjectSize size) -> void {
        attr1 = (attr1.to_ulong() & 0b0011111111111111) |
                (utils::value_of(size) << 14);
    }

    auto flip_horizontally(bool flip) -> void {
        attr1[12] = flip;
    }

    auto flip_vertically(bool flip) -> void {
        attr1[13] = flip;
    }

    auto base_tile(int index) -> void {
        attr2 = (attr2.to_ulong() & ~0b111111111) | (index & 0b111111111);
    }

    auto priority(ObjectPriority priority) -> void {
        attr2 = (attr2.to_ulong() & ~0b11000000000) |
                (utils::value_of(priority) << 10);
    }

    auto palette(int index) -> void {
        attr2 = (attr2.to_ulong() & ~(0xff << 12)) | ((index & 0xff) << 12);
    }
};

auto oam_entry(int index) -> OAMEntry&;

auto sprite_tile(int index) -> gba::display::map::Tile&;

}

#endif
