#include <libgba/arch/display/obj.h>

using gba::display::Color;

namespace {

static auto& palette = *new (reinterpret_cast<void*>(0x0500'0200)) std::array<Color, 256>{};

}

namespace gba {

std::array<Color, 256>& display::obj_palette() {
    return palette;
}

}
