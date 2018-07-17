#ifndef GBA_DRIVERS_DISPLAY_WINDOW_H
#define GBA_DRIVERS_DISPLAY_WINDOW_H

#include "control.h"
#include "layers.h"

namespace gba::display {

/**
 * Usable window layer.
 */
enum class Window {
    /**
     * Window layer 0.
     */
    WIN0,
    /**
     * Window layer 1.
     */
    WIN1,
    /**
     * Object layer window.
     */
    OBJ,
};

/**
 * Controls window layer position.
 */
struct WindowPosition {
    /**
     * Window's right boundary coordinate.
     */
    uint8_t right;
    /**
     * Window's left boundary coordinate.
     */
    uint8_t left;

private:
    uint8_t __do_not_plz[2];

public:
    /**
     * Window's bottom boundary coordinate.
     */
    uint8_t bottom;
    /**
     * Window's upper boundary coordinate.
     */
    uint8_t top;
};

/**
 * Controls window layer properties.
 */
class WindowControl {
public:
    /**
     * Enables/disables Window 0 for a background layer.
     *
     * @remarks Using Layer::OBJ is UB.
     */
    void window0_enable(Layer layer, bool enabled=true) {
        data[utils::value_of(layer)] = enabled;
    }

    /**
     * Enables/disables Window 1 for a background layer.
     *
     * @remarks Using Layer::OBJ is UB.
     */
    void window1_enable(Layer layer, bool enabled=true) {
        data[utils::value_of(layer) + 8] = enabled;
    }

    /**
     * Enables/disables Outer Window for a background layer.
     *
     * @remarks Using Layer::OBJ is UB.
     */
    void outer_enable(Layer layer, bool enabled=true) {
        data[utils::value_of(layer) + 16] = enabled;
    }

    /**
     * Enables/disables Object Window for a background layer.
     */
    void obj_enable(Layer layer, bool enabled=true) {
        data[utils::value_of(layer) + 24] = enabled;
    }

private:
    std::bitset<32> data;
};

static auto& window0 = *new (reinterpret_cast<void*>(0x0400'0040)) WindowPosition{};
static auto& window1 = *new (reinterpret_cast<void*>(0x0400'0042)) WindowPosition{};
static auto& window_control = *new (reinterpret_cast<void*>(0x0400'0048)) WindowControl{};

/**
 * Makes window layer visible/hidden.
 *
 * @param window Window layer.
 * @param visible True if visible, False if hidden.
 */
inline void window_visible(Window window, bool visible=true) {
    gba::arch::registers::display
        ::lcd_control[13 + utils::value_of(window)] = visible;
}

}

#endif
