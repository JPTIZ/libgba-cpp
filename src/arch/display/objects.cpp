#include <libgba-cpp/arch/display/objects.h>

using gba::display::Color;
using gba::display::RawPalette;

namespace {

static auto& obj_palette =
    *new (reinterpret_cast<void*>(0x0500'0200)) RawPalette<256>{};

}

namespace gba {

RawPalette<256>& display::obj_palette() {
    return ::obj_palette;
}

}
