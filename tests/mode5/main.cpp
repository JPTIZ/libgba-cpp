#include <drivers/display/video.h>

void fill_screen(const gba::display::Color& color) {
    for (auto i = 0u; i < 160*120; ++i) {
        gba::display::mode5::vram(i) = color;
    }
}

int main() {
    using namespace gba::display;

    change_mode(Mode::MODE5);
    force_blank(false);

    fill_screen(Color{31, 0, 0});

    while (true) {}
}
