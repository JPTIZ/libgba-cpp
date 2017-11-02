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
    /**
     * No special effect.
     */
    NONE,
    /**
     * Alpha blend effect.
     */
    ALPHA_BLEND,
    /**
     * Change brightness to a lighter coloring.
     */
    BRIGHTEN,
    /**
     * Change brightness to a more shady coloring.
     */
    DARKEN,
};


/**
 * Enables layer as color effect's first target.
 */
void first_target(Layer layer, bool enabled=true);

/**
 * Enables backdrop as color effect's first target.
 */
void backdrop_first_target(bool enabled=true);


/**
 * Enables layer as color effect's second target.
 */
void second_target(Layer layer, bool enabled=true);


/**
 * Enables backdrop as color effect's second target.
 */
void backdrop_second_target(bool enabled=true);

/**
 * Changes current special effect.
 */
void select(SpecialEffect effect);

/**
 * AlphaBlend first target intensity.
 */
inline auto& blend_a_strength() {
    return gba::architecture::registers::display::blend_a;
}

/**
 * AlphaBlend second target intensity.
 */
inline auto& blend_b_strength() {
    return gba::architecture::registers::display::blend_b;
}

}

#endif
