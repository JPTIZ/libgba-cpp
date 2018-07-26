#include <libgba-cpp/arch/display/layers.h>

#include <libgba-cpp/arch/registers.h>
#include <libgba-cpp/utils/general.h>

namespace {

using gba::display::BackgroundControl;
using gba::display::RawPalette;

using gba::arch::registers::display::bg_controls;

static auto& bg_palette = *new (reinterpret_cast<void*>(0x0500'0000)) RawPalette<256>{};

}

BackgroundControl& gba::display::bg_control(gba::display::Layer layer) {
    return *(reinterpret_cast<BackgroundControl*>(0x0400'0008) + utils::value_of(layer));
}

RawPalette<256>& gba::display::bg_palette() {
    return ::bg_palette;
}
