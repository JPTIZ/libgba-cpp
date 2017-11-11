#include <engine/graphics/palette.h>

void gba::graphics::load_palette(const Palette& palette) {
    for (auto i = 0u; i < 10u; ++i) {
        display::bg_palette()[i + 1] = palette[i];
    }
}
