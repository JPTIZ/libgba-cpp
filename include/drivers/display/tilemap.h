#ifndef GBA_DRIVERS_DISPLAY_TILEMAP_H
#define GBA_DRIVERS_DISPLAY_TILEMAP_H

#include "control.h"
#include "layers.h"

/**
 * Map manipulation elements.
 */
namespace gba::display::map {


namespace details {

/**
 * A pair of tile pixels.
 */
class TileIndex {
public:
    TileIndex(uint32_t& data, int index):
        data{data},
        index{index}
    {}

    void operator=(unsigned value) {
        data = (data & (~0xfu << index)) | ((value & 0xfu) << index);
    }

private:
    uint32_t& data;
    const int index;
};

}

/**
 * A single 8x8 tile.
 */
class Tile {
public:
    Tile() = default;

    Tile(std::array<uint32_t, 8> rows):
        rows_{move(rows)}
    {}

    /**
     * Row of palette indexes in tile.
     */
    auto operator()(unsigned x, unsigned y) {
        return details::TileIndex(rows_[y], x << 2);
    }

private:
    std::array<uint32_t, 8> rows_{};
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
