#ifndef GBA_DRIVERS_DISPLAY_CONTROL_H
#define GBA_DRIVERS_DISPLAY_CONTROL_H

#include <bitset>

#include "../utility.h"

namespace gba::display {

enum class Mode {
    MODE0,
    MODE1,
    MODE2,
    MODE3,
    MODE4,
    MODE5,
};

enum class Page {
    PAGE0,
    PAGE1,
};

static auto& lcd_control = *new (reinterpret_cast<void*>(0x0400'0000)) std::bitset<16>{};

inline volatile auto& vcount() {
    return *reinterpret_cast<std::uint16_t*>(0x0400'0006);
}

inline void change_mode(Mode mode) {
    lcd_control = (lcd_control.to_ulong() & ~0b111u) | utils::value_of(mode);
}

inline void select_page(Page page) {
    lcd_control[4] = utils::value_of(page);
}

inline void oam_in_hblank(bool flag) {
    lcd_control[5] = flag;
}

inline void force_blank(bool flag) {
    lcd_control[7] = flag;
}

}

#endif
