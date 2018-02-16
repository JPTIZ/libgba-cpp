#ifndef GBA_ENGINE_GRAPHICS_MAPS_H
#define GBA_ENGINE_GRAPHICS_MAPS_H

#include <array>

#include <libgba-cpp/drivers/display/tilemap.h>

#include "geometry.h"

namespace gba::engine::graphics {

template <std::size_t TilesetLength>
using TileSet = std::array<display::map::Tile, TilesetLength>;


template <std::size_t MapLength>
class TileMap {
    using contents_t = std::array<uint16_t, MapLength>;
public:
    TileMap(contents_t& contents):
        contents{contents}
    {}

    auto& length() const {
        return MapLength;
    }

    const auto& operator[](int i) const {
        return contents[i];
    }

private:
    const contents_t& contents;
};


class Map {
public:
    virtual auto length() const -> std::size_t = 0;
    virtual auto operator()(int x, int y) -> int& = 0;
    virtual auto operator()(int x, int y) const -> const int& = 0;
};


template <std::size_t TilesetLength, std::size_t MapLength>
class BaseMap: Map {
    using tileset_t = TileSet<TilesetLength>;
    using tilemap_t = TileMap<MapLength>;
public:
    BaseMap(tileset_t& tileset, tilemap_t& tilemap, geometry::Size size = {0, 0}):
        _tileset{tileset},
        _tilemap{tilemap},
        size{size}
    {}

    auto length() const override {
        return _tilemap.length();
    }

    auto& tileset() {
        return _tileset;
    }

    const auto& tileset() const {
        return _tileset;
    }

    auto& tilemap() {
        return _tilemap;
    }

    const auto& tilemap() const {
        return _tilemap;
    }

    auto& operator()(int x, int y) override {
        return _tilemap[x + size.width * y];
    }

    const auto& operator()(int x, int y) const override {
        return _tilemap[x + size.width * y];
    }

private:
    tileset_t& _tileset;
    tilemap_t& _tilemap;
    geometry::Size size;
};

}

#endif
