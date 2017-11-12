#include <engine/graphics/palette.h>

void gba::graphics::load_palette(const Palette& palette) {
    for (auto i = 0u; i < palette.size(); ++i) {
        display::bg_palette()[i] = palette[i].value();
    }
}
