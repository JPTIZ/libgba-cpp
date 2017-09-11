#ifndef LIBGBACPP_DRIVERS_ARCHITECTURE_REGISTERS_H
#define LIBGBACPP_DRIVERS_ARCHITECTURE_REGISTERS_H

#include <cstdint>
#include <bitset>

namespace gba::architecture::registers {

template <typename T>
auto& at(unsigned address) {
    return *new (reinterpret_cast<void*>(address)) T{};
}

template <>
auto& at<uint16_t>(unsigned address) {
    return *reinterpret_cast<uint16_t*>(address);
}

//----------------------------------------------------------------------------
// Display
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// IO
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// CPU
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Sound
//----------------------------------------------------------------------------

static auto& channel1_sweep      = at<std::bitset<16>>(0x0400'0060);
static auto& channel1_envelope   = at<std::bitset<16>>(0x0400'0062);
static auto& channel1_control    = at<std::bitset<16>>(0x0400'0064);

static auto& channel2_envelope   = at<std::bitset<16>>(0x0400'0068);
static auto& channel2_control    = at<std::bitset<16>>(0x0400'006c);

static auto& channel3_wave_bank  = at<std::bitset<16>>(0x0400'0070);
static auto& channel3_length     = at<std::bitset<16>>(0x0400'0072);
static auto& channel3_control    = at<std::bitset<16>>(0x0400'0074);

static auto& channel4_envelope   = at<std::bitset<16>>(0x0400'0078);
static auto& channel4_noise      = at<std::bitset<16>>(0x0400'007c);

static auto& sound_dmg_control   = at<std::bitset<16>>(0x0400'0080);
static auto& directsound_control = at<std::bitset<16>>(0x0400'0082);
static auto& sound_status        = at<std::bitset<16>>(0x0400'0084);

static auto& sound_bias          = at<std::bitset<16>>(0x0400'0088);

static auto& wave_ram0_l         = at<std::bitset<16>>(0x0400'0090);
static auto& wave_ram0_h         = at<std::bitset<16>>(0x0400'0092);

static auto& wave_ram1_l         = at<std::bitset<16>>(0x0400'0094);
static auto& wave_ram1_h         = at<std::bitset<16>>(0x0400'0096);

static auto& wave_ram2_l         = at<std::bitset<16>>(0x0400'0098);
static auto& wave_ram2_h         = at<std::bitset<16>>(0x0400'009a);

static auto& wave_ram3_l         = at<std::bitset<16>>(0x0400'009c);
static auto& wave_ram3_h         = at<std::bitset<16>>(0x0400'009e);

static auto& dsa_fifo_l          = at<std::bitset<16>>(0x0400'00a0);
static auto& dsa_fifo_h          = at<std::bitset<16>>(0x0400'00a2);
static auto& dsb_fifo_l          = at<std::bitset<16>>(0x0400'00a4);
static auto& dsb_fifo_h          = at<std::bitset<16>>(0x0400'00a6);

}

#endif
