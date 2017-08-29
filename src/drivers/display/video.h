#ifndef GBA_DRIVERS_DISPLAY_VIDEO_H
#define GBA_DRIVERS_DISPLAY_VIDEO_H

#include <array>

#include "control.h"

namespace gba::display {

union VRAM_Data{
    uint16_t s;
    uint8_t c[2];
};

static auto& vram_data = *new (reinterpret_cast<void*>(0x0600'0000)) std::array<VRAM_Data, 0x18000 / 2>{};

namespace mode3 {
    static constexpr auto screen_width = 240;
    static constexpr auto screen_height = 160;

    auto& vram(int x, int y) {
        return vram_data[x + screen_width * y].s;
    }
}

namespace mode4 {
    static constexpr auto screen_width = 240;
    static constexpr auto screen_height = 160;

    auto& vram(int x, int y) {
        return vram_data[x + screen_width * y / 2].c[y & 1];
    }
}

namespace mode5 {
    static constexpr auto screen_width = 160;
    static constexpr auto screen_height = 128;

    auto& vram(int x, int y) {
        return vram_data[x + screen_width * y].s;
    }
}

inline void vsync() {
    while (vcount >= 160) {}
    while (vcount < 160) {}
}

}

#endif
