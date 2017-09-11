#ifndef LIBGBACPP_DRIVERS_SOUND_SOUND_H
#define LIBGBACPP_DRIVERS_SOUND_SOUND_H

namespace gba::sound {



/**
 * Must be on for registers to be accessed and for sound to play.
 */
void master_enabled(bool);

/**
 * General
 */

enum class Channel {
    SQUARE1,
    SQUARE2,
    WAVE,
    NOISE,
};

void enable_channel(Channel channel);

void left_volume(unsigned);
void right_volume(unsigned);

void enable_left(Channel);
void enable_right(Channel);

void master_volume(unsigned);

void sound_rate(unsigned);
void timed(bool);
void reset();
void sweep_number(unsigned);

enum class SweepMode {
    INCREMENT,
    DECREMENT,
};
void sweep_mode(SweepMode);

void sweep_step_time(unsigned);

}

#endif
