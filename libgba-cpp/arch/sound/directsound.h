#ifndef LIBGBACPP_DRIVERS_SOUND_DIRECT_SOUND_H
#define LIBGBACPP_DRIVERS_SOUND_DIRECT_SOUND_H

#include "sound.h"

namespace gba::sound {

/**
 * Direct Sound
 */

enum class DSoundRatio {
    RATIO50,
    RATIO100,
};

void ds_volume(Volume);

void dsa_volume_ratio(DSoundRatio);
void dsa_enabled_left(bool);
void dsa_enabled_right(bool);
void dsa_use_timer(bool);
void dsa_fifo_reset();

void dsb_volume_ratio(DSoundRatio);
void dsb_enabled_left(bool);
void dsb_enabled_right(bool);
void dsb_use_timer(bool);
void dsb_fifo_reset();

}

#endif
