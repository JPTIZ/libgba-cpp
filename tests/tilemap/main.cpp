#include <engine/graphics/tilemap.h>

#include "sample_map.h"

using namespace gba::display;
using namespace gba::graphics;
using namespace resources::maps;


int main() {
    force_blank(true);

    const auto map = gba::graphics::Map{
        sample_tileset,
        sample_tilemap,
        layer0_tilemap,
        null_tilemap,
        null_tilemap,
        gba::graphics::MapSize::TEXT_256X256
    };

    change_mode(Mode::MODE0);
    layer_visible(Layer::BG0);
    layer_visible(Layer::BG1);

    load_map(map);

    force_blank(false);

    auto i = 0u;
    while (true) {
        bg_oy(Layer::BG1) = -i;
        vsync();

        ++i;
    }
}
