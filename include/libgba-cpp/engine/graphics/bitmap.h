#ifndef LIBGBA_ENGINE_BITMAP_H
#define LIBGBA_ENGINE_BITMAP_H

#include <cstdint>

#include <libgba-cpp/engine/graphics/tilemap.h>


namespace gba::graphics {

class Bitmap {
public:
    Bitmap(const Palette& palette);

    Bitmap(const Palette& palette,
           uint8_t data[]
    ):
        palette_{palette},
        data_{data}
    {}

    auto data() const {
        return data_;
    }

    const auto& palette() const {
        return palette_;
    }

private:
    const Palette& palette_;
    const uint8_t* data_;
};

}

#endif
