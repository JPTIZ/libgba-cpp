#ifndef LIBGBA_ENGINE_PALETTE_H
#define LIBGBA_ENGINE_PALETTE_H

#include <array>
#include <cstdint>

#include "graphics.h"

namespace gba::graphics {

/**
 * Bitmap color palette.
 */
class Palette {
public:
    template <std::size_t N>
    Palette(const std::array<Color, N>& palette):
        size_{N},
        palette_{palette.data()}
    {}

    template <std::size_t N>
    Palette(const std::array<uint16_t, N>& palette):
        size_{N},
        palette_{palette.data()}
    {}

    /**
     * @param palette Color array.
     * @param size Color array size.
     */
    Palette(const uint16_t palette[],
            std::size_t size
    ):
        size_{size},
        palette_{reinterpret_cast<const Color*>(palette)}
    {}

    const auto& colors() const {
        return palette_;
    }

    /**
     * Accesses a single entry at given index.
     */
    auto operator[](std::size_t i) {
        return palette_[i];
    }

    /**
     * Reads a single entry at given index.
     */
    const auto operator[](std::size_t i) const {
        return palette_[i];
    }

    /**
     * Number of colors on palette.
     */
    auto size() const {
        return size_;
    }

private:
    std::size_t size_;
    const Color* palette_;
};

/**
 * Loads palette into memory.
 */
void load_palette(const Palette&);

}

#endif
