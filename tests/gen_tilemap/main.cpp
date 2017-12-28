#include <engine/graphics/tilemap.h>

#include "map001.h"

using namespace gba::display;
using namespace gba::graphics;
using namespace test::maps;


int main() {
    force_blank(true);

    const auto& map = map001;

    change_mode(Mode::MODE0);
    layer_visible(Layer::BG0);
    layer_visible(Layer::BG1);

    load_map(map);

    force_blank(false);

    while (true) {
        vsync();
    }
}
