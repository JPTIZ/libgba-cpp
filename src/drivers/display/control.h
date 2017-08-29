#ifndef GBA_DRIVERS_DISPLAY_CONTROL_H
#define GBA_DRIVERS_DISPLAY_CONTROL_H

#include <bitset>

namespace gba::display {

static auto& lcd_control = *new (reinterpret_cast<void*>(0x0400'0000)) std::bitset<16>{};
static volatile auto& vcount = *reinterpret_cast<std::uint16_t*>(0x0400'0006);

}

#endif
