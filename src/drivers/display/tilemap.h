#ifndef GBA_DRIVERS_DISPLAY_TILEMAP_H
#define GBA_DRIVERS_DISPLAY_TILEMAP_H

#include "control.h"
#include "layers.h"

namespace gba::display::map {

struct Tile {
    std::array<uint32_t, 8> rows;
};

static auto& tiles = *new (reinterpret_cast<void*>(0x0600'0000)) std::array<Tile, 0x40>{};
static auto& map = *new (end(tiles)) std::array<Tile, 0x1024>{};

}

#endif
