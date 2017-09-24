#ifndef GBA_DRIVERS_DISPLAY_VIDEO_H
#define GBA_DRIVERS_DISPLAY_VIDEO_H

#include <array>

#include "control.h"

namespace gba::display {

/**
 * Pixel in GBA Color format.
 */
class Color {
    /**
     * Constructs black color.
     */
    Color() = default;

    /**
     * Constructs color from specified value.
     *
     * @param value Value (in X1B5G5R5 format).
     */
    Color(unsigned value):
        value_{static_cast<uint16_t>(value)}
    {}

    /**
     * Constructs color with given RGB values.
     *
     * @param r Red channel intensity.
     * @param g Green channel intensity.
     * @param b Blue channel intensity.
     */
    Color(int r, int g, int b):
        value_{static_cast<uint16_t>(
                ((r & 0x1f) << 0) |
                ((g & 0x1f) << 5) |
                ((b & 0x1f) << 10)
              )}
    {}

    /**
     * Returns color value (in X1B5G5R5 format).
     *
     * @returns Color value.
     */
    auto value() const {
        return value_;
    }

    /**
     * Red channel intensity.
     */
    auto r() const {
        return value_ & 0x1f;
    }

    /**
     * Green channel intensity.
     */
    auto g() const {
        return (value_ >> 5) & 0x1f;
    }

    /**
     * Blue channel intensity.
     */
    auto b() const {
        return (value_ >> 10) & 0x1f;
    }

private:
    uint16_t value_ = 0u;
};

/**
 * Single data from VRAM.
 */
union VRAMData {
    /**
     * VRAM data as pixel value.
     */
    uint16_t s;
    /**
     * VRAM data as two palette index consecutive values.
     *
     * @remarks GBA VRAM is little-endian.
     */
    uint8_t c[2];
    /**
     * VRAM data as color.
     */
    Color color;
};

/**
 * GBA's VRAM data array.
 */
std::array<VRAMData, 0x18000 / 2>& vram_data();

/**
 * Display Mode 3 elements.
 */
namespace mode3 {
    /**
     * Screen resolution's width.
     */
    static constexpr auto screen_width = 240;
    /**
     * Screen resolution's height.
     */
    static constexpr auto screen_height = 160;

    /**
     * Gets video pixel at given coordinates.
     *
     * @param x Pixel's X coordinate.
     * @param y Pixel's Y coordinate.
     *
     * @returns Pixel color in given coordinates.
     */
    auto& vram(int x, int y) {
        return vram_data()[x + screen_width * y].color;
    }

    /**
     * Gets video pixel at given VRAM index.
     *
     * @param index Pixel index.
     *
     * @returns Pixel color in given VRAM index.
     */
    auto& vram(int index) {
        return vram_data()[index].color;
    }
}

/**
 * Display Mode 4 elements.
 */
namespace mode4 {
    /**
     * Screen resolution's width.
     */
    static constexpr auto screen_width = 240;
    /**
     * Screen resolution's height.
     */
    static constexpr auto screen_height = 160;

    /**
     * Gets video pixel at given coordinates.
     *
     * @param x Pixel's X coordinate.
     * @param y Pixel's Y coordinate.
     *
     * @returns Palette index in given coordinates.
     */
    auto& vram(int x, int y) {
        return vram_data()[x + screen_width * y / 2].c[y & 1];
    }

    /**
     * Gets video pixel at given VRAM index.
     *
     * @param index Pixel index.
     *
     * @returns Palette index in given VRAM index.
     */
    auto& vram(int index) {
        return vram_data()[index].c;
    }
}

/**
 * Display Mode 5 elements.
 */
namespace mode5 {
    /**
     * Screen resolution's width.
     */
    static constexpr auto screen_width = 160;
    /**
     * Screen resolution's height.
     */
    static constexpr auto screen_height = 128;

    /**
     * Gets video pixel at given coordinates.
     *
     * @param x Pixel's X coordinate.
     * @param y Pixel's Y coordinate.
     *
     * @returns Color value in given coordinates.
     */
    auto& vram(int x, int y) {
        return vram_data()[x + screen_width * y].s;
    }

    /**
     * Gets video pixel at given VRAM index.
     *
     * @param index Pixel index.
     *
     * @returns Color value in given index.
     */
    auto& vram(int index) {
        return vram_data()[index].s;
    }
}

/**
 * Skip current VBlank stage and waits for the next one to begin.
 */
inline void vsync() {
    while (vcount() >= 160) {}
    while (vcount() < 160) {}
}

}

#endif
