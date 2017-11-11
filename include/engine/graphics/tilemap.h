#ifndef LIBGBA_ENGINE_TILEMAP_H
#define LIBGBA_ENGINE_TILEMAP_H

#include <array>
#include <cstdint>
#include <utility>

#include <drivers/display/tilemap.h>
#include "palette.h"

#include "graphics.h"

namespace gba::graphics {

using MapSize = gba::display::MapSize;

using Tile = gba::display::map::Tile;

/**
 * Sequence of tiles for tilemap filling.
 */
class Tileset {
public:
    template <std::size_t N>
    Tileset(const Palette& palette,
            const std::array<Tile, N>& tiles):
        palette_{palette},
        count_{N},
        tiles_{reinterpret_cast<const Tile*>(tiles.data())}
    {}

    Tileset(const Palette& palette,
            const Tile tiles[],
            unsigned count):
        palette_{palette},
        count_{count},
        tiles_{tiles}
    {}

    auto length() const {
        return count_;
    }

    const auto& data() const {
        return tiles_;
    }

    const auto& palette() const {
        return palette_;
    }

    const auto& operator[](int i) const {
        return tiles_[i];
    }

private:
    const Palette& palette_;
    const unsigned count_;
    const Tile* tiles_;
};

/**
 * A single mapping of indexes to tiles.
 */
class Tilemap {
public:
    template <std::size_t N>
    Tilemap(const std::array<uint16_t, N>& tiles):
        count_{N},
        tiles_{reinterpret_cast<const uint16_t*>(tiles.data())}
    {}

    Tilemap(const uint16_t tiles[], unsigned count):
        count_{count},
        tiles_{tiles}
    {}

    const auto length() const {
        return count_;
    }

    const auto& tiles() const {
        return tiles_;
    }

    const auto& operator[](int i) const {
        return tiles_[i];
    }

private:
    const unsigned count_;
    const uint16_t* tiles_;
};


class Map {
public:
    Map(const Tileset& tileset,
        const Tilemap& tilemap,
        MapSize size):
        tileset_{tileset},
        tilemap_{tilemap},
        size_{size}
    {}

    const auto& tileset() const {
        return tileset_;
    }

    const auto& tilemap() const {
        return tilemap_;
    }

    auto size() const {
        return size_;
    }

    auto width() const {
        return extract_size(size_).width;
    }

    auto height() const {
        return extract_size(size_).height;
    }

private:
    const Tileset& tileset_;
    const Tilemap& tilemap_;
    MapSize size_;
};

/**
 * Loads tileset into tile memory.
 */
inline void load_tileset(const Tileset& tileset) {
    for (auto i = 0u; i < tileset.length(); ++i) {
        display::map::tileset()[i + 1] = tileset[i];
    }
}

/**
 * Setups memory with given tilemap.
 */
inline void load_map(const Map& map) {
    const auto& tileset = map.tileset();
    const auto& tilemap = map.tilemap();

    const auto& palette = tileset.palette();
    load_tileset(map.tileset());

    for (auto i = 0u; i < tilemap.length(); ++i) {
        display::map::tilemap()[i] = tilemap[i];
    }
    bg_control(display::Layer::BG0).screen_base_block(1);
}

}

#endif
