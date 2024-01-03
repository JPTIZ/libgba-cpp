#ifndef LIBGBA_ENGINE_TILEMAP_H
#define LIBGBA_ENGINE_TILEMAP_H

#include <array>
#include <cstdint>

#include <libgba-cpp/arch/display/layers.h>
#include <libgba-cpp/arch/display/tilemap.h>
#include "palette.h"


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

    auto length() const {
        return count_;
    }

    const auto& tiles() const {
        return tiles_;
    }

    auto operator[](int i) const {
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
        const MapSize size):
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

    const auto& layer(const gba::display::Layer layer) const {
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

    const auto& layer0() const {
        return layer0_;
    }

private:
    const Tileset& tileset_;
    const Tilemap& layer0_;
    const Tilemap& layer1_;
    const Tilemap& layer2_;
    const Tilemap& layer3_;
    const MapSize size_;
};

/**
 * Loads map into map memory.
 */
inline void load_tilemap(const Tilemap& tilemap, int screenblock, int charblock) {
    const auto base = 0x400 * screenblock + 0x2000 * charblock;
    for (auto i = 0u; i < tilemap.length(); ++i) {
        display::map::tilemap()[i + base] = tilemap[i];
    }
}

/**
 * Loads tileset into tile memory.
 */
inline void load_tileset(const Tileset& tileset) {
    for (auto i = 0u; i < tileset.length(); ++i) {
        display::map::tileset()[i] = tileset[i];
    }
}

/**
 * Setup and load map into memory.
 */
inline void load_map(const Map& map) {
    using gba::display::Layer;
    using gba::display::BGPriority;
    using gba::display::PaletteMode;

    /* load the palette from the image into palette memory*/
    load_palette(map.tileset().palette());

    /* load the image into char block 0 (16 bits at a time) */
    load_tileset(map.tileset());

    /* set all control the bits in this register */
    constexpr auto layers = std::array{Layer::BG0, Layer::BG1, Layer::BG2, Layer::BG3};
    constexpr auto priorities = std::array{
        BGPriority::LOWEST,
        BGPriority::LOW,
        BGPriority::HIGH,
        BGPriority::HIGHEST,
    };
    auto itlayer = std::begin(layers);
    auto priority = std::begin(priorities);
    for (auto i = 0u; i < 4; ++i) {
        const auto layer = *itlayer;

        auto control = bg_control(layer);
        control.screen_base_block(16 + i);
        control.priority(*priority);
        control.palette_mode(PaletteMode::PALETTE_256);
        bg_control(layer) = control;

        gba::graphics::load_tilemap(map.layer(layer), 16 + i, 0);

        ++itlayer;
        ++priority;
    }
}

}

#endif
