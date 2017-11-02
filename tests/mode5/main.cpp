#include <drivers/display/video.h>
#include <drivers/display/layers.h>

void fill_screen(const gba::display::Color& color) {
    for (auto i = 0u; i < 160*120; ++i) {
        gba::display::mode5::vram(i) = color;
    }
}

int main() {
    using namespace gba::display;

    change_mode(Mode::MODE5);
    layer_visible(Layer::BG2);

    force_blank(false);

    fill_screen(Color{31, 0, 0});

    auto first = true;
    while (true) {
        vsync();
        first = !first;
        fill_screen(Color{31 >> first, 0, 0});
        mode5::flip_pages();
    }
}
