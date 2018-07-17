#include <libgba/arch/cpu/interrupts.h>

#include <libgba/arch/display/video.h>
#include <libgba/arch/display/layers.h>

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
