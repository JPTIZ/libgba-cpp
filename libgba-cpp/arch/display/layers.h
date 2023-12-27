#ifndef GBA_DRIVERS_DISPLAY_LAYERS_H
#define GBA_DRIVERS_DISPLAY_LAYERS_H


#include <libgba-cpp/arch/registers.h>
#include <libgba-cpp/arch/display/video.h>
#include <libgba-cpp/utils/geometry.h>


namespace gba::display {

/**
 * A map layer.
 */
enum class Layer {
    BG0,
    BG1,
    BG2,
    BG3,
    OBJ,
};


/**
 * Backgroud priority. `HIGHEST` means the layer will be above all others.
 */
enum class BGPriority {
    HIGHEST = 0,
    HIGH,
    LOW,
    LOWEST,
};


/**
 * Color palette mode.
 */
enum class PaletteMode {
    /**
     * 16 palettes with 16 colors each.
     */
    PALETTE_16,

    /**
     * 1 palette with 256 colors.
     */
    PALETTE_256,
};


/**
 * Map overflow behaviour.
 */
enum class Overflow {
    /**
     * Hides map overflow area.
     */
    TRANSPARENT = 0,

    /**
     * Wraps overflowed map area trough screen.
     */
    WRAPAROUND,
};


/**
 * Map size (in pixels).
 */
enum class MapSize {
    /**
     * 256x256 map (in Text Mode).
     */
    TEXT_256X256 = 0,

    /**
     * 512x256 map (in Text Mode).
     */
    TEXT_512X256,

    /**
     * 256x512 map (in Text Mode).
     */
    TEXT_256X512,

    /**
     * 512x512 map (in Text Mode).
     */
    TEXT_512X512,

    /**
     * 128x128 map (in Rotation/Scaling Mode).
     */
    ROTSCAL_128X128 = 10,

    /**
     * 256x256 map (in Rotation/Scaling Mode).
     */
    ROTSCAL_256X256,

    /**
     * 512x512 map (in Rotation/Scaling Mode).
     */
    ROTSCAL_512X512,

    /**
     * 1024x1024 map (in Rotation/Scaling Mode).
     */
    ROTSCAL_1024X1024,
};


constexpr geometry::Size extract_size(MapSize size) {
    switch (size) {
        case MapSize::TEXT_256X256:
            return {256, 256};
        case MapSize::TEXT_256X512:
            return {256, 512};
        case MapSize::TEXT_512X256:
            return {512, 256};
        case MapSize::ROTSCAL_128X128:
            return {128, 128};
        case MapSize::ROTSCAL_256X256:
            return {256, 256};
        case MapSize::TEXT_512X512:
        case MapSize::ROTSCAL_512X512:
            return {512, 512};
        case MapSize::ROTSCAL_1024X1024:
            return {1024, 1024};
    }
}


/**
 * Controls properties of a background.
 */
class BackgroundControl {
public:
    /**
     * Changes background priority.
     */
    void priority(gba::display::BGPriority value) {
        data = (data & (~0b11u)) | utils::value_of(value);
    }

    /**
     * Changes background's character block base index.
     */
    void char_base_block(unsigned base) {
        data = (data & (~0b1100u)) | ((base & 0b11u) << 2);
    }

    /**
     * Enables mosaic effect for background.
     */
    void mosaic(bool flag) {
        data = (data & ~0b100000u) | (flag << 6);
    }

    /**
     * Changes background's palette mode.
     *
     * @param mode New palette mode.
     *
     * @see PaletteMode
     */
    void palette_mode(gba::display::PaletteMode mode) {
        data = (data & (~0b1000000u)) | (utils::value_of(mode) << 7);
    }

    /**
     * Changes background's screen block base index.
     */
    void screen_base_block(unsigned base) {
        data = (data & ~0b111110000000u) | ((base & 0b11111u) << 8);
    }

    /**
     * Changes background's overflow method.
     *
     * @param method New overflow method.
     *
     * @see Overflow
     */
    void overflow(gba::display::Overflow method) {
        data = (data & ~(0b1u << 13)) | (utils::value_of(method) << 13);
    }

    /**
     * Changes background's size (in pixels).
     *
     * @param size_ New background size.
     *
     * @see MapSize
     */
    void resize(gba::display::MapSize size_) {
        data = (data & (~(0b11u << 14))) | (utils::value_of(size_) & 0b11u);
    }

private:
    uint16_t data;
};


/**
 * Gets layer's background control.
 *
 * @remarks Using Layer::OBJ is UB.
 */
BackgroundControl& bg_control(Layer layer);


/**
 * Changes background X offset.
 */
inline auto& bg_ox(Layer layer) {
    return *(reinterpret_cast<uint16_t*>(0x0400'0010) + 2 * utils::value_of(layer));
}


/**
 * Changes background Y offset.
 */
inline auto& bg_oy(Layer layer) {
    return *(reinterpret_cast<uint16_t*>(0x0400'0012) + 2 * utils::value_of(layer));
}


/**
 * Shows/hide layer.
 */
inline void layer_visible(Layer layer, bool visible=true) {
    auto& lcd_control = gba::arch::registers::display::lcd_control;
    lcd_control[8 + utils::value_of(layer)] = visible;
}


RawPalette<256>& bg_palette();

}

#endif
