#ifndef LIBGBACPP_DRIVERS_SOUND_DIRECT_SOUND_H
#define LIBGBACPP_DRIVERS_SOUND_DIRECT_SOUND_H

namespace gba::sound {

/**
 * Direct Sound
 */

enum class DSoundRatio {
    RATIO50,
    RATIO100,
};

void dsa_volume_ratio(DSoundRatio);
void dsa_enabled(bool);
void dsa_use_timer(bool);
void dsa_fifo_reset(bool);

void dsb_volume_ratio(DSoundRatio);
void dsb_enabled(bool);
void dsb_use_timer(bool);
void dsb_fifo_reset(bool);

}

#endif
