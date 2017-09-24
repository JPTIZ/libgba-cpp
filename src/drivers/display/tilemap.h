#ifndef GBA_DRIVERS_DISPLAY_TILEMAP_H
#define GBA_DRIVERS_DISPLAY_TILEMAP_H

#include "control.h"
#include "layers.h"

/**
 * Map manipulation elements.
 */
namespace gba::display::map {

/**
 * A single tile.
 */
struct Tile {
    /**
     * Row of palette indexes in tile.
     */
    std::array<uint32_t, 8> rows;
};

/**
 * Tiles to fill maps with.
 */
std::array<Tile, 0x40>& tileset();

/**
 * The game map.
 */
std::array<uint16_t, 1024>& tilemap();

}

#endif
