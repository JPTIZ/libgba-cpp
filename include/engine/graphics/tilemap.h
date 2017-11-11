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
        const Tilemap& layer0,
        const Tilemap& layer1,
        const Tilemap& layer2,
        const Tilemap& layer3,
        MapSize size):
        tileset_{tileset},
        layer0_{layer0},
        layer1_{layer1},
        layer2_{layer2},
        layer3_{layer3},
        size_{size}
    {}

    const auto& tileset() const {
        return tileset_;
    }

    const auto& layer(gba::display::Layer layer) const {
        switch (layer) {
            case display::Layer::BG0: return layer0_;
            case display::Layer::BG1: return layer1_;
            case display::Layer::BG2: return layer2_;
            case display::Layer::BG3: return layer3_;
            default: return layer0_;
        }
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
    const Tilemap& layer0_;
    const Tilemap& layer1_;
    const Tilemap& layer2_;
    const Tilemap& layer3_;
    MapSize size_;
};

/**
 * Loads map into map memory.
 */
inline void load_tilemap(const Tilemap& tilemap, int screenblock) {
    for (auto i = 0u; i < tilemap.length(); ++i) {
        display::map::tilemap()[i + 0x400 * screenblock] = tilemap[i];
    }
}

/**
 * Loads tileset into tile memory.
 */
inline void load_tileset(const Tileset& tileset) {
    for (auto i = 0u; i < tileset.length(); ++i) {
        display::map::tileset()[i + 1] = tileset[i];
    }
}

/**
 * Setup and load map into memory.
 */
inline void load_map(const Map& map) {
    const auto& tileset = map.tileset();

    display::layer_visible(display::Layer::BG0);

    load_palette(tileset.palette());
    load_tileset(map.tileset());

    using gba::display::Layer;
    load_tilemap(map.layer(Layer::BG0), 0);

    bg_control(display::Layer::BG0).screen_base_block(1);
}

}

#endif
