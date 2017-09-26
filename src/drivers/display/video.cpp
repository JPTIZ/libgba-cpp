#include "video.h"

namespace {

using gba::display::Color;
using gba::display::VRAMData;

static auto& vram_data = *new (reinterpret_cast<void*>(0x0600'0000)) std::array<VRAMData, 0x18000 / 2>{};
static auto& bg_palette = *new (reinterpret_cast<void*>(0x0500'0000)) std::array<Color, 256>{};

}

std::array<VRAMData, 0x18000 / 2>& gba::display::vram_data() {
    return ::vram_data;
}

std::array<Color, 256>& gba::display::bg_palette() {
    return ::bg_palette;
}

