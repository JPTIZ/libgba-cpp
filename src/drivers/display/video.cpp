#include "video.h"

namespace {

using gba::display::VRAMData;

static auto& vram_data = *new (reinterpret_cast<void*>(0x0600'0000)) std::array<VRAMData, 0x18000 / 2>{};

}

std::array<VRAMData, 0x18000 / 2>& gba::display::vram_data() {
    return ::vram_data;
}

