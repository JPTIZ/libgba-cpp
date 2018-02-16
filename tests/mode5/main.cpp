#include <libgba-cpp/drivers/display/video.h>
#include <libgba-cpp/drivers/display/layers.h>

void fill_screen(const gba::display::Color& color) {
    for (auto i = 0u; i < 160*120; ++i) {
        gba::display::mode5::vram(i) = color;
    }
}

int main() {
    using namespace gba::display;

    force_blank(true);
    change_mode(Mode::MODE5);
    layer_visible(Layer::BG2);

    fill_screen(Color{31, 0, 0});
    mode5::flip_pages();
    force_blank(false);

    auto first = false;
    while (true) {
        vsync();
        first = not first;
        fill_screen(Color{31 >> first, 0, 0});
        mode5::flip_pages();
    }
}
