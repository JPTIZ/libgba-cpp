#ifndef RESOURCES_SAMPLE_TILES_H
#define RESOURCES_SAMPLE_TILES_H

#include <array>

#include <engine/graphics/tilemap.h>
#include <engine/graphics/palette.h>

namespace resources::maps {

using gba::graphics::Color;
using gba::graphics::Tile;
using gba::graphics::Tileset;
using gba::graphics::Palette;

const std::array<Color, 7> raw_sample_palette = {
    Color{0x1f, 0x00, 0x00},
    Color{0x00, 0x1f, 0x00},
    Color{0x00, 0x00, 0x17},
    Color{0x1f, 0x1f, 0x00},
    Color{0x00, 0x1f, 0x17},
    Color{0x1f, 0x00, 0x17},
    Color{0x1f, 0x1f, 0x1f},
};

const std::array<Tile, 8> sample_tiles = {
    Tile{
     {0x33333333,
      0x33333333,
      0x33333333,
      0x33333333,
      0x33333333,
      0x33333333,
      0x33333333,
      0x33333333}},

    {{0x11111111,
      0x12222222,
      0x12111111,
      0x12111111,
      0x12111111,
      0x12111111,
      0x12111122,
      0x12111121}},

    {{0x11111111,
      0x22222222,
      0x11111111,
      0x11111111,
      0x11111111,
      0x11111111,
      0x22222222,
      0x11111111}},

    {{0x11111111,
      0x22222221,
      0x11111121,
      0x11111121,
      0x11111121,
      0x11111121,
      0x22111121,
      0x12111121}},

    {{0x12111121,
      0x12111122,
      0x12111111,
      0x12111111,
      0x12111111,
      0x12111111,
      0x12222222,
      0x11111111}},

    {{0x12111121,
      0x22111121,
      0x11111121,
      0x11111121,
      0x11111121,
      0x11111121,
      0x22222221,
      0x11111111}},

    {{0x12111121,
      0x12111121,
      0x12111121,
      0x12111121,
      0x12111121,
      0x12111121,
      0x12111121,
      0x12111121}},
};

const Palette sample_palette{raw_sample_palette};
const Tileset sample_tileset{sample_palette, sample_tiles};

}

#endif

