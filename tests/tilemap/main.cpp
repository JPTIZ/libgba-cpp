#include <engine/graphics/tilemap.h>

#include "sample_map.h"

int main() {
    using namespace gba::display;
    using namespace gba::graphics;
    change_mode(Mode::MODE0);

    load_map(resources::maps::map1);

    while (true) {
        vsync();
    }
}
