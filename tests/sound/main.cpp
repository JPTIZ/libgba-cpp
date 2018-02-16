#include <drivers/arch/registers.h>
#include <drivers/sound/sound.h>
#include <drivers/display/video.h>
#include <drivers/display/layers.h>

const signed char sample[] = {
    1, -1, 100, -100, 127, -127, 0, 32, 32, 32, 0xf, 0x0, 0xd, 0xa
};

void enable_dmas() {
    using namespace gba::architecture::registers::io;
    using namespace gba::architecture::registers::sound;

    dma1_source = (uint32_t)((size_t)sample);
    dma1_destination = (uint32_t)((size_t)&dsa_fifo_0);

    timer0_counter = 0xffff - 761;
    timer0_control = 0x80;

    dma1_control = (1 << 6) | // Fixed
                   (1 << 9) | // Repeat
                   (1 << 10) | // Word (32-bit)
                   (1 << 12) | // FI
                   (1 << 13) | // FO
                   (1 << 15)   // Enabled
                   ;
}

int main() {
    using namespace gba::sound;

    enable(true);
    enable_left(Channel::SQUARE1);

    auto i = 0;
    using namespace gba::display;
    using namespace gba::display::mode3;

    change_mode(Mode::MODE3);
    layer_visible(Layer::BG2);

    while (true) {
        for (auto y = 0; y < screen_height; ++y) {
            for (auto x = 0; x < screen_width; ++x) {
                vram(x, y) = Color{i, 0, 0};
            }
        }
        i = (i + 1) % 32;

        enable_dmas();
    }
}
