#ifndef GBA_DRIVERS_DISPLAY_CONTROL_H
#define GBA_DRIVERS_DISPLAY_CONTROL_H

#include "control.h"

namespace gba::display {

static auto& vram_data = *new (reinterpret_cast<void*>(0x0600'0000)) std::array<std::uint16_t, 0x17fff>{};

namespace mode3 {
    static const auto screen_width = 240;
    static const auto screen_height = 160;

    static auto vram(int x, int y) {
        return vram_data[x + screen_width * y / 2];
    }
}

namespace mode4 {
    static const auto screen_width = 240;
    static const auto screen_height = 160;

    static auto vram(int x, int y) {
        return (*reinterpret_cast<std::array<std::uint8_t, vram_data.size()>*>(vram_data))[x + screen_width * y];
    }
}

namespace mode5 {
    static const auto screen_width = 160;
    static const auto screen_height = 128;

    static auto vram(int x, int y) {
        return vram_data[x + screen_width * y];
    }
}

inline void vsync() {
    while (vcount >= 160) {}
    while (vcount < 160) {}
}

}
