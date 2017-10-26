#ifndef LIBGBA_ENGINE_BITMAP_H
#define LIBGBA_ENGINE_BITMAP_H

#include <cstdint>

#include "graphics.h"
#include "palette.h"
#include "tilemap.h"

namespace gba::graphics {

class PalettedBitmap {
public:
    PalettedBitmap(
            int width,
            int height,
            Palette& palette);

    PalettedBitmap(
            int width,
            int height,
            Palette& palette,
            uint8_t data[]
    ):
        width_{width},
        height_{height},
        palette_{palette},
        data_{data}
    {}

    auto width() const {
        return width_;
    }

    auto height() const {
        return height_;
    }

    auto data() const {
        return data_;
    }

    auto palette() const {
        return palette_;
    }

private:
    const int width_;
    const int height_;
    const Palette& palette_;
    const uint8_t* data_;
};

class TiledBitmap {
public:
    TiledBitmap(
            int width,
            int height,
            const Tileset& tileset,
            const Tilemap& tilemap):
        width_{width},
        height_{height},
        tileset_{tileset},
        tilemap_{tilemap}
    {}

    auto tileset() const {
        return tileset_;
    }

    auto tilemap() const {
        return tilemap_;
    }

    auto width() const {
        return width_;
    }

    auto height() const {
        return height_;
    }

private:
    const int width_;
    const int height_;
    const Tileset& tileset_;
    const Tilemap& tilemap_;
};

}

#endif
