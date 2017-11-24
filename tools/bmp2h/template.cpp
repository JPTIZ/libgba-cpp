#include "${name}.h"

namespace {
using gba::graphics::Color;
using gba::graphics::Palette;
using gba::graphics::Tile;
using gba::graphics::Tileset;

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

}

const Palette ${namespace}::maps::${name}_palette{raw_${name}_palette};

const Tileset ${namespace}::maps::${name}_tileset{
    ${name}_palette,
    ${name}_tiles
};
