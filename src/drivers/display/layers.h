#ifndef GBA_DRIVERS_DISPLAY_LAYERS_H
#define GBA_DRIVERS_DISPLAY_LAYERS_H

#include <array>

#include "control.h"
#include "video.h"

namespace gba::display {

enum class Layer {
    BG0,
    BG1,
    BG2,
    BG3,
    OBJ,
};

enum class BGPriority {
    HIGHEST = 0,
    HIGH,
    LOW,
    LOWEST,
};

enum class PaletteMode {
    PALETTE_16,
    PALETTE_256,
};

enum class Overflow {
    TRANSPARENT = 0,
    WRAPAROUND,
};

enum class ScreenSize {
    TEXT_256X256 = 0,
    TEXT_512X256,
    TEXT_256X512,
    TEXT_512X512,

    ROTSCAL_128X128 = 0,
    ROTSCAL_256X256,
    ROTSCAL_512X512,
    ROTSCAL_1024X1024,
};

class BGControl {
public:
    void priority(BGPriority value) {
        data = (data & (~0b11u)) | utils::value_of(value);
    }

    void char_base_block(unsigned base) {
        data = (data & (~0b1100u)) | ((base & 0b11u) << 2);
    }

    void mosaic(bool flag) {
        data = (data & ~0b100000) | (flag << 6);
    }

    void palette_mode(PaletteMode mode) {
        data = (data & ~0b1000000) | (utils::value_of(mode) << 7);
    }

    void screen_base_block(unsigned base) {
        data = (data & (~0x1fu << 8)) | ((base & 0x1f) << 8);
    }

    void overflow(Overflow value) {
        data = (data & ~(0b1u << 13)) | (utils::value_of(value) << 13);
    }

    void size(ScreenSize size_) {
        data = (data & (~(0b11u << 14))) | utils::value_of(size_);
    }

private:
    std::uint16_t data;
};

static auto& bg_palette = *new (reinterpret_cast<void*>(0x0500'0000)) std::array<Color, 256>{};
static auto& bg_controls = *new (reinterpret_cast<void*>(0x0400'0008)) std::array<BGControl, 4>{};

static auto& bg_ox(Layer layer) {
    return *(reinterpret_cast<uint16_t*>(0x0400'0010) + 2 * utils::value_of(layer));
}

static auto& bg_oy(Layer layer) {
    return *(reinterpret_cast<uint16_t*>(0x0400'0012) + 2 * utils::value_of(layer));
}

inline void layer_visible(Layer layer, bool visible=true) {
    lcd_control[8 + utils::value_of(layer)] = visible;
}

}

#endif
