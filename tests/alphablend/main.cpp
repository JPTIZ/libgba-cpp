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

    tiles[11] = {
        0x77777777,
        0x77777777,
        0x77777777,
        0x77777777,
        0x77777777,
        0x77777777,
        0x77777777,
        0x77777777,
    };
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

    for (auto i = 0; i < 9; ++i) {
        map::map[(i % 3) + 3 + 32 * (3 + i / 3) + 0x800] = 0xb;
    }

    for (auto i = 0; i < 9; ++i) {
        map::map[(i % 3) + 5 + 32 * (5 + i / 3) + 0xC00] = 0xb;
    }
}

int main() {
    layer_visible(Layer::BG0);
    layer_visible(Layer::BG1);
    layer_visible(Layer::BG2);
    layer_visible(Layer::BG3);

    bg_controls[0].screen_base_block(1);
    bg_controls[1].screen_base_block(2);
    bg_controls[2].screen_base_block(3);
    bg_controls[3].screen_base_block(4);

    bg_controls[0].priority(BGPriority::LOWEST);
    bg_controls[1].priority(BGPriority::LOW);
    bg_controls[2].priority(BGPriority::HIGH);
    bg_controls[3].priority(BGPriority::HIGHEST);

    bg_oy(Layer::BG1) = -16;

    color_effects.first_target(Layer::BG3);
    color_effects.first_target(Layer::BG2);
    color_effects.first_target(Layer::BG1);
    color_effects.second_target(Layer::BG2);
    color_effects.second_target(Layer::BG1);
    color_effects.second_target(Layer::BG0);
    color_effects.select(SpecialEffect::ALPHA_BLEND);

    alphablend_strength.first = 8;
    alphablend_strength.second = 8;


    copy_palette();
    copy_tiles();

    gen_map();

    auto i = 0;

    while (true) {
        vsync();

        bg_ox(Layer::BG1) = -i;

        ++i;
    }
}

