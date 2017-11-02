#ifndef LIBGBA_ENGINE_TILEMAP_H
#define LIBGBA_ENGINE_TILEMAP_H

#include <array>
#include <cstdint>
#include <utility>

#include "graphics.h"

namespace gba::graphics {

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

    auto operator()(unsigned x, unsigned y) {
        return details::TileIndex(rows_[y], x << 2);
    }

private:
    std::array<uint32_t, 8> rows_{};
};

/**
 * Sequence of tiles for tilemap filling.
 */
class Tileset {
public:
    template <std::size_t N>
    Tileset(const std::array<Tile, N> tiles):
        count_{N},
        tiles_{reinterpret_cast<const Tile*>(tiles.data())}
    {}

    Tileset(const Tile tiles[], int count):
        count_{count},
        tiles_{tiles}
    {}

    auto length() const {
        return count_;
    }

    const auto data() const {
        return tiles_;
    }

    const auto operator[](int i) const {
        return tiles_[i];
    }

private:
    const int count_;
    const Tile* tiles_;
};

/**
 * A single mapping of indexes to tiles.
 */
class Tilemap {
public:
    Tilemap(const uint16_t tiles[], int count):
        count_{count},
        tiles_{tiles}
    {}

    const auto length() const {
        return count_;
    }

    const auto tiles() const {
        return tiles_;
    }

private:
    const int count_;
    const uint16_t* tiles_;
};

}

#endif
