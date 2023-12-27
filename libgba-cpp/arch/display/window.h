#ifndef GBA_DRIVERS_DISPLAY_WINDOW_H
#define GBA_DRIVERS_DISPLAY_WINDOW_H

#include <bitset>

#include <libgba-cpp/arch/display/layers.h>

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
    [[maybe_unused]]
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


WindowPosition& window0();
WindowPosition& window1();
WindowControl& window_control();

/**
 * Makes window layer visible/hidden.
 *
 * @param window Window layer.
 * @param visible True if visible, False if hidden.
 */
inline void set_window_visible(Window window, bool visible=true) {
    gba::arch::registers::display
        ::lcd_control[13 + utils::value_of(window)] = visible;
}

}

#endif
