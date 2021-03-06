#include <libgba-cpp/arch/registers.h>
#include <libgba-cpp/arch/sound/sound.h>

void enable_dmas() {
    using namespace gba::arch::registers::io;

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

    set_enabled(true);
    set_left(Channel::SQUARE1, true);

    enable_dmas();

    while (true) {
    }
}
