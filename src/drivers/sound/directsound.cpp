#include <libgba-cpp/drivers/sound/directsound.h>

#include <libgba-cpp/drivers/arch/registers.h>
#include <libgba-cpp/utility.h>

using utils::value_of;
using namespace gba::architecture::registers::sound;

namespace gba {

void sound::ds_volume(Volume volume) {
    directsound_control =
        (directsound_control.to_ulong() & 0b11) | (value_of(volume) & 0b11);
}

// A side

void sound::dsa_volume_ratio(sound::DSoundRatio ratio) {
    directsound_control[2] = ratio == DSoundRatio::RATIO100;
}

void sound::dsa_enabled_left(bool enabled) {
    directsound_control[9] = enabled;
}

void sound::dsa_enabled_right(bool enabled) {
    directsound_control[8] = enabled;
}

void sound::dsa_use_timer(bool use) {
    directsound_control[10] = use;
}

void sound::dsa_fifo_reset() {
    directsound_control[11] = true;
}

// B side

void sound::dsb_volume_ratio(sound::DSoundRatio ratio) {
    directsound_control[3] = ratio == DSoundRatio::RATIO100;
}

void sound::dsb_enabled_left(bool enabled) {
    directsound_control[13] = enabled;
}

void sound::dsb_enabled_right(bool enabled) {
    directsound_control[12] = enabled;
}

void sound::dsb_use_timer(bool use) {
    directsound_control[14] = use;
}

void sound::dsb_fifo_reset() {
    directsound_control[15] = true;
}

}
