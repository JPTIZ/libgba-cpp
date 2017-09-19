#include "sound.h"

#include "../architecture/registers.h"
#include "../utility.h"

using utils::value_of;
using namespace gba::architecture::registers::sound;

namespace gba {

void sound::enable(bool flag) {
    status[7] = flag;
}

void sound::enable_left(sound::Channel channel, bool enabled) {
    dmg_control[0x8 + value_of(channel)] = true;
}

void sound::enable_right(sound::Channel channel, bool enabled) {
    dmg_control[0xc + value_of(channel)] = true;
}

void sound::left_volume(unsigned volume) {
    dmg_control =
        (dmg_control.to_ulong() & (~0b111u << 4)) | (volume & 0b111);
}

void sound::right_volume(unsigned volume) {
    dmg_control =
        (dmg_control.to_ulong() & ~0b111u) | (volume & 0b111);
}

}
