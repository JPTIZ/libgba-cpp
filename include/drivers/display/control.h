#ifndef GBA_DRIVERS_DISPLAY_CONTROL_H
#define GBA_DRIVERS_DISPLAY_CONTROL_H

#include <bitset>

#include <drivers/arch/registers.h>
#include <drivers/utility.h>

/**
 * Elements for GBA's display manipulation.
 */
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
inline volatile auto& vcount() {
    return gba::architecture::registers::display::vcount;
}

/**
 * Changes current display mode.
 *
 * @remarks Changing the display mode will make PPU interpret VRAM data
 *          differently. Remember to update data when changing modes.
 */
inline void change_mode(Mode mode) {
    auto& lcd_control = gba::architecture::registers::display::lcd_control;
    lcd_control = (lcd_control.to_ulong() & ~0b111u) | utils::value_of(mode);
}

/**
 * Select VRAM buffer page.
 *
 * @param page The new page for PPU to read.
 */
inline void select_page(Page page) {
    auto& lcd_control = gba::architecture::registers::display::lcd_control;
    lcd_control[4] = utils::value_of(page);
}

/**
 * Allow OAM access during vblank.
 *
 * @param flag True if allow access, False otherwise.
 */
inline void oam_in_hblank(bool flag) {
    auto& lcd_control = gba::architecture::registers::display::lcd_control;
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
    auto& lcd_control = gba::architecture::registers::display::lcd_control;
    lcd_control[7] = flag;
}

}

#endif
