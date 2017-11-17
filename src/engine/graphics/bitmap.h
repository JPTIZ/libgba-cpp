#ifndef GBA_ENGINE_GRAPHICS_BITMAP_H
#define GBA_ENGINE_GRAPHICS_BITMAP_H

#include <array>
#include <experimental/array>

#include <drivers/display/video.h>
#include <engine/graphics/palette.h>

#include "geometry.h"

namespace gba::graphics {

template <std::size_t W, std::size_t H>
class Bitmap {
    using Size = geometry::Size;
    using contents_t = std::array<uint8_t, W * H>;

public:
    Bitmap(Size size):
        contents(size.width, size.height),
        size{size}
    {}

    Bitmap(Palette& palette);

private:
    Palette& palette = Palette::EMPTY;
    contents_t& contents;
    Size size;
};

}

#endif
