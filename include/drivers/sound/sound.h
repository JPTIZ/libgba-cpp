#ifndef LIBGBACPP_DRIVERS_SOUND_SOUND_H
#define LIBGBACPP_DRIVERS_SOUND_SOUND_H

namespace gba::sound {



/**
 * Must be on for registers to be accessed and for sound to play.
 */
void enable(bool);

/**
 * General
 */

enum class Channel {
    SQUARE1,
    SQUARE2,
    WAVE,
    NOISE,
};

enum class Volume {
    VOLUME_25,
    VOLUME_50,
    VOLUME_100,
};

void left_volume(unsigned);
void right_volume(unsigned);

void enable_left(Channel, bool enabled=true);
void enable_right(Channel, bool enabled=true);

void sweep_number(unsigned);

enum class SweepMode {
    INCREMENT,
    DECREMENT,
};
void sweep_mode(SweepMode);

void sweep_step_time(unsigned);

}

#endif
