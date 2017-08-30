#ifndef GBA_DRIVERS_DISPLAY_EFFECTS_H
#define GBA_DRIVERS_DISPLAY_EFFECTS_H

#include "control.h"
#include "layers.h"

namespace gba::display {

class MosaicRegister {
public:
    MosaicRegister() = default;

    void bg_h(unsigned amount) {
        data = (data & ~(0b1111u << 0)) | ((amount & 0b1111) << 0);
        mosaic_register = data;
    }

    void bg_v(unsigned amount) {
        data = (data & ~(0b1111u << 4)) | ((amount & 0b1111) << 4);
        mosaic_register = data;
    }

    void obj_h(unsigned amount) {
        data = (data & ~(0b1111u << 8)) | ((amount & 0b1111) << 8);
        mosaic_register = data;
    }

    void obj_v(unsigned amount) {
        data = (data & ~(0b1111u << 0xc)) | ((amount & 0b1111) << 0xc);
        mosaic_register = data;
    }

private:
    uint16_t data = 0;
    uint16_t& mosaic_register = *reinterpret_cast<uint16_t*>(0x0400'004c);
};

enum class SpecialEffect {
    NONE,
    ALPHA_BLEND,
    BRIGHTNESS_WHITE,
    BRIGHTNESS_BLACK,
};

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

static auto mosaic_level = MosaicRegister{};
static auto& color_effects = *new (reinterpret_cast<void*>(0x0400'0050)) ColorEffectRegister{};
static auto& alphablend_strength = *new (reinterpret_cast<void*>(0x0400'0052)) AlphaBlendStrength{};
static auto& brightness = *reinterpret_cast<uint16_t*>(0x0400'0054);

}

#endif
