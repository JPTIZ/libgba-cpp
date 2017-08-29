#include <display/layers.h>
#include <display/control.h>

#include "sample_tiles.h"

using namespace gba::display;
using namespace gba::display::map;

using namespace resources::maps;

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
    map::map[0] = 0x1;
}

int main() {
    layer_visible(Layer::BG0);
    bg_controls[0].screen_base_block(1);

    copy_palette();
    copy_tiles();

    gen_map();

    while (true) {
        vsync();
    }
}
