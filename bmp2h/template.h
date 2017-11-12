#ifndef ${namespace.upper()}_MAPS_${name.upper()}_H
#define ${namespace.upper()}_MAPS_${name.upper()}_H

#include <array>

#include <engine/graphics/tilemap.h>
#include <engine/graphics/palette.h>

namespace ${namespace}::maps {

using gba::graphics::Color;
using gba::graphics::Tile;
using gba::graphics::Tileset;
using gba::graphics::Palette;

const std::array<Color, ${n_colors}> raw_${name}_palette = {
    Color
%% for left, right in colors|chunks(2)
    {${'%2d' % left.r}, ${'%2d' % left.g}, ${'%2d' % left.b}}, {${'%2d' % right.r}, ${'%2d' % right.g}, ${'%2d' % right.b}},
%% endfor
};

const std::array<Tile, ${n_tiles}> ${name}_tiles = {
    Tile
%% for tile in tiles
    {{
    %% for left, right in tile|chunks(2)
        ${'0x%0x' % left}, ${'0x%0x' % right},
    %% endfor
    }},
%% endfor
};

const Palette sample_palette{raw_${name}_palette};
const Tileset sample_tileset{${name}_palette, ${name}_tiles};

}

#endif
