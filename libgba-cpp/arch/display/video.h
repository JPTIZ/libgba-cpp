#ifndef GBA_DRIVERS_DISPLAY_VIDEO_H
#define GBA_DRIVERS_DISPLAY_VIDEO_H

#include <array>

#include <libgba-cpp/arch/registers.h>
#include <libgba-cpp/utils/general.h>

namespace gba::display {

/**
 * Display Mode.
 */
enum class Mode {
    MODE0, /**< Character Display Mode 0 */
    MODE1, /**< Character Display Mode 1 */
    MODE2, /**< Character Display Mode 2 */
    MODE3, /**< Bitmap Display Mode 3 */
    MODE4, /**< Bitmap Display Mode 4 */
    MODE5, /**< Bitmap Display Mode 5 */
};


/**
 * Video buffer page selection.
 */
enum class Page {
    PAGE0, /**< Video page 0. */
    PAGE1, /**< Video page 1. */
};


/**
 * Vertical count.
 *
 * @return Current scanline number processed by PPU.
 */
inline volatile const auto& vcount() {
    return gba::arch::registers::display::vcount;
}


/**
 * Changes current display mode.
 *
 * @remarks Changing the display mode will make PPU interpret VRAM data
 *          differently. Remember to update data when changing modes.
 */
inline auto change_mode(Mode mode) -> void {
    auto& lcd_control = gba::arch::registers::display::lcd_control;
    lcd_control = (lcd_control.to_ulong() & ~0b111u) | utils::value_of(mode);
}


/**
 * Select VRAM buffer page.
 *
 * @param page The new page for PPU to read.
 */
inline void select_page(Page page) {
    auto& lcd_control = gba::arch::registers::display::lcd_control;
    lcd_control[4] = utils::value_of(page);
}


/**
 * Allow OAM access during vblank.
 *
 * @param flag True if allow access, False otherwise.
 */
inline void oam_in_hblank(bool flag) {
    auto& lcd_control = gba::arch::registers::display::lcd_control;
    lcd_control[5] = flag;
}


/**
 * Forces blank screen.
 *
 * @remarks Forcing blank screen _may_ speed up access to VRAM.
 *
 * @param flag True to force blank screen, False to disable.
 */
inline void force_blank(bool flag) {
    auto& lcd_control = gba::arch::registers::display::lcd_control;
    lcd_control[7] = flag;
}


/**
 * Pixel in GBA Color format.
 */
class Color {
public:
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


template <class VRAMDataType>
inline auto vram_data() {
  constexpr auto VRAM_BASE_ADDRESS = 0x0600'0000;
  return reinterpret_cast<VRAMDataType*>(VRAM_BASE_ADDRESS);
}


/**
 * Display Mode 3 elements.
 */
namespace mode3 {
    using VRAMData = std::uint16_t;

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
    inline auto vram(int x, int y) -> VRAMData& {
        return vram_data<VRAMData>()[x + screen_width * y];
    }

    /**
     * Gets video pixel at given VRAM index.
     *
     * @param index Pixel index.
     *
     * @returns Pixel color in given VRAM index.
     */
    inline auto vram(int index) -> VRAMData& {
        return vram_data<VRAMData>()[index];
    }
}


/**
 * Display Mode 4 elements.
 */
namespace mode4 {
    using VRAMData = std::array<std::uint8_t, 2>;

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
    inline auto& vram(int x, int y) {
        return vram_data<VRAMData>()[x + screen_width * y / 2][y & 1];
    }

    /**
     * Gets video pixel at given VRAM index.
     *
     * @param index Pixel index.
     *
     * @returns Palette index in given VRAM index.
     */
    inline auto& vram(int index) {
        return vram_data<VRAMData>()[index];
    }
}


/**
 * Display Mode 5 elements.
 */
namespace mode5 {
    using VRAMData = Color;

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
    Color& vram(int x, int y);

    /**
     * Gets video pixel at given VRAM index.
     *
     * @param index Pixel index.
     *
     * @returns Color value in given index.
     */
    Color& vram(int index);

    /**
     * Gets current selected page.
     */
    Page page();

    /**
     * Toggles current selected page.
     */
    void flip_pages();
}


/**
 * Skip current VBlank stage and waits for the next one to begin.
 */
inline auto vsync() -> void {
    while (vcount() >= 160) {}
    while (vcount() < 160) {}
}

template <std::size_t N>
using RawPalette = std::array<Color, N>;

}

#endif
