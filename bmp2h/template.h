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
%% for color in colors
    {${color.r}, ${color.g}, ${color.b}},
%% endfor
};

const std::array<Tile, ${n_tiles}> ${name}_tiles = {
    Tile
%% for tile in tiles
    {{
    %% for row in tile
        ${'0x%0x' % row},
    %% endfor
    }},
%% endfor
};

const Palette sample_palette{raw_${name}_palette};
const Tileset sample_tileset{${name}_palette, ${name}_tiles};

}

#endif
