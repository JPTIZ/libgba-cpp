#include <libgba-cpp/engine/graphics/sprite.h>

using namespace gba::graphics;
using namespace gba::geometry;

const auto raw_palette = std::array<Color, 2>{
    Color{31, 0, 0},
    Color{ 0,31, 0},
};
const auto sample_palette = Palette{raw_palette};
const auto sample_bitmap = Bitmap{
    sample_palette,
    std::move(std::array<uint8_t, 1024>{
        0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
    }.data())
};

int main() {
    auto test_sprite = Sprite(sample_bitmap, Size{32, 32});
    test_sprite.visible(true);
    load_obj_palette(test_sprite, 0);

    while (true) {
        refresh_sprites();
    }
}
