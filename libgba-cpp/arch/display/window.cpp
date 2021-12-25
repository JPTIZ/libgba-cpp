#include <new>

#include <libgba-cpp/arch/display/window.h>

using gba::display::WindowPosition;
using gba::display::WindowControl;

namespace {
    auto const win0_address = reinterpret_cast<WindowPosition*>(0x0400'0040);
    auto const win1_address = reinterpret_cast<WindowPosition*>(0x0400'0042);
    auto const win2_address = reinterpret_cast<WindowPosition*>(0x0400'0048);
    auto& window0 = *new (win0_address) WindowPosition{};
    auto& window1 = *new (win1_address) WindowPosition{};
    auto& window_control = *new (win2_address) WindowControl{};
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
