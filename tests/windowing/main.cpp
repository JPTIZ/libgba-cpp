#include <display/layers.h>
#include <display/control.h>
#include <display/effects.h>

#include "sample_tiles.h"
#include "sample_map.h"

using namespace gba::display;
using namespace gba::display::map;

using namespace resources::maps;
using namespace test;

void copy_palette() {
    for (auto i = 0; i < sample_palette.size(); ++i) {
        bg_palette[i + 1] = sample_palette[i];
    }
}

void copy_tiles() {
    for (auto i = 0; i < sample_tiles.size(); ++i) {
        tiles[i + 1] = sample_tiles[i];
    }
}

void gen_map() {

    for (auto i = 0; i < layer0.size(); ++i) {
        auto x = i % 8;
        auto y = i / 8;
        map::map[x + 32 * y] = layer0[i];
    }

    for (auto i = 0; i < layer1.size(); ++i) {
        map::map[i + 3 + 32 * 3 + 0x400] = layer1[i];
    }
}

int main() {
    layer_visible(Layer::BG0);
    layer_visible(Layer::BG1);

    bg_controls[0].screen_base_block(1);
    bg_controls[0].priority(BGPriority::LOWEST);
    bg_controls[1].screen_base_block(2);
    bg_controls[1].priority(BGPriority::LOW);

    bg_ox(Layer::BG1) = 16;
    bg_oy(Layer::BG1) = -16;

    bg_controls[0].mosaic(true);
    bg_controls[1].mosaic(true);
    mosaic_level.bg_h(0);
    mosaic_level.bg_v(0);

    copy_palette();
    copy_tiles();

    gen_map();

    auto i = 0;

    while (true) {
        vsync();

        mosaic_level.bg_h(i);
        mosaic_level.bg_v(i);

        ++i;
    }
}

