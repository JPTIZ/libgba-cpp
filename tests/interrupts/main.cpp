#include <drivers/cpu/interrupts.h>

#include <drivers/display/video.h>
#include <drivers/display/layers.h>

using namespace gba::display;
using namespace gba::cpu;

int main() {
    //setup_interrupts();

    vblank_interrupt(true);
    bg_palette()[0] = Color{0, 0x1f, 0};
    while (true) {
        halt();
        bg_palette()[0] = Color{0, 0x1f, 0};
        halt();
        bg_palette()[0] = Color{0x1f, 0, 0};
    }
}
