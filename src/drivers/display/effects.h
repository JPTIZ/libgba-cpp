#ifndef GBA_DRIVERS_DISPLAY_EFFECTS_H
#define GBA_DRIVERS_DISPLAY_EFFECTS_H

#include "control.h"
#include "layers.h"

namespace gba::display {

/**
 * Mosaic intensity for Background layers.
 */
void mosaic_bg_level(unsigned width, unsigned height);

/**
 * Mosaic intensity for Object layer.
 */
void mosaic_obj_level(unsigned width, unsigned height);


/**
 * Possible special color effects by hardware.
 */
enum class SpecialEffect {
    NONE, /**< No special effect. **/
    ALPHA_BLEND, /**< Alpha blend effect. **/
    BRIGHTNESS_WHITE, /**< Change brightness to a more lighter coloring. **/
    BRIGHTNESS_BLACK, /**< Change brightness to a more shady coloring. **/
};


/**
 * Controls a register for color effect control.
 */
class ColorEffectRegister {
public:
    void first_target(Layer layer, bool enabled=true) {
        data[utils::value_of(layer)] = enabled;
    }

    void backdrop_first_target(bool enabled=true) {
        data[5] = enabled;
    }

    void second_target(Layer layer, bool enabled=true) {
        data[utils::value_of(layer) + 8] = enabled;
    }

    void backdrop_second_target(bool enabled=true) {
        data[13] = enabled;
    }

    void select(SpecialEffect effect) {
        data = (data.to_ulong() & ~(0b11u << 6)) | ((utils::value_of(effect) & 0b11u) << 6);
    }

private:
    std::bitset<16> data;
};

struct AlphaBlendStrength {
    uint8_t first;
    uint8_t second;
};

static auto& color_effects = *new (reinterpret_cast<void*>(0x0400'0050)) ColorEffectRegister{};
static auto& alphablend_strength = *new (reinterpret_cast<void*>(0x0400'0052)) AlphaBlendStrength{};
static auto& brightness = *reinterpret_cast<uint16_t*>(0x0400'0054);

}

#endif
