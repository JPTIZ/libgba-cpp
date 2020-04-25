#include <libgba-cpp/arch/display/window.h>

using gba::display::WindowPosition;
using gba::display::WindowControl;

namespace {
    auto& window0 = *new (reinterpret_cast<void*>(0x0400'0040)) WindowPosition{};
    auto& window1 = *new (reinterpret_cast<void*>(0x0400'0042)) WindowPosition{};
    auto& window_control = *new (reinterpret_cast<void*>(0x0400'0048)) WindowControl{};
}

namespace gba {

WindowPosition& display::window0() {
    return ::window0;
}

WindowPosition& display::window1() {
    return ::window1;
}

WindowControl& display::window_control() {
    return ::window_control;
}

}
