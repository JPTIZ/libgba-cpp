#include <libgba-cpp/arch/display/objects.h>

using gba::display::Color;
using gba::display::RawPalette;

namespace {

static auto const obj_palette_address = reinterpret_cast<RawPalette<256>*>(0x0500'0200);
static auto& obj_palette =
    *new (obj_palette_address) RawPalette<256>{};

}

namespace gba {

RawPalette<256>& display::obj_palette() {
    return ::obj_palette;
}

}
