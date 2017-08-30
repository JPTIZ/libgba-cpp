#ifndef GBA_DRIVERS_DISPLAY_WINDOW_H
#define GBA_DRIVERS_DISPLAY_WINDOW_H

#include "control.h"

namespace gba::display {

enum class Window {
    WIN0,
    WIN1,
    OBJ,
};

struct WindowSize {
    uint8_t right;
    uint8_t left;

    uint8_t __do_not_plz[2];

    uint8_t bottom;
    uint8_t top;
};

class WindowControl {
public:
    void window0_enable(Layer layer, bool enabled=true) {
        data[utils::value_of(layer)] = enabled;
    }

    void window1_enable(Layer layer, bool enabled=true) {
        data[utils::value_of(layer) + 8] = enabled;
    }

    void outer_enable(Layer layer, bool enabled=true) {
        data[utils::value_of(layer) + 16] = enabled;
    }

    void obj_enable(Layer layer, bool enabled=true) {
        data[utils::value_of(layer) + 24] = enabled;
    }

private:
    std::bitset<32> data;
};

static auto& window0 = *new (reinterpret_cast<void*>(0x0400'0040)) WindowSize{};
static auto& window1 = *new (reinterpret_cast<void*>(0x0400'0042)) WindowSize{};
static auto& window_control = *new (reinterpret_cast<void*>(0x0400'0048)) WindowControl{};

inline void window_visible(Window window, bool visible=true) {
    lcd_control[13 + utils::value_of(window)] = visible;
}

}

#endif
