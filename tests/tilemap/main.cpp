#include <engine/graphics/tilemap.h>

#include "sample_map.h"

int main() {
    using namespace gba::display;
    using namespace gba::graphics;
    change_mode(Mode::MODE0);

    bg_control(Layer::BG0).screen_base_block(1);
    layer_visible(Layer::BG0);

    load_map(resources::maps::map1);

    while (true) {
        vsync();
    }
}
