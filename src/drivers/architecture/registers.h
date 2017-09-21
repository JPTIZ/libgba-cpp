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

/**
 * Display Registers
 */
namespace display {

static auto& lcd_control               = at<std::bitset<16>>(0x0400'0000);
static auto& green_swap                = at<std::bitset<16>>(0x0400'0002);
static auto& lcd_status                = at<std::bitset<16>>(0x0400'0004);
static volatile auto& vcount           = at<uint16_t>(0x0400'0006);

static auto& bg0_control               = at<std::bitset<16>>(0x0400'0008);
static auto& bg1_control               = at<std::bitset<16>>(0x0400'000a);
static auto& bg2_control               = at<std::bitset<16>>(0x0400'000c);
static auto& bg3_control               = at<std::bitset<16>>(0x0400'000e);

static auto& bg0_x_offset              = at<uint16_t>(0x0400'0010);
static auto& bg0_y_offset              = at<uint16_t>(0x0400'0012);
static auto& bg1_x_offset              = at<uint16_t>(0x0400'0014);
static auto& bg1_y_offset              = at<uint16_t>(0x0400'0016);
static auto& bg2_x_offset              = at<uint16_t>(0x0400'0018);
static auto& bg2_y_offset              = at<uint16_t>(0x0400'001a);
static auto& bg3_x_offset              = at<uint16_t>(0x0400'001c);
static auto& bg3_y_offset              = at<uint16_t>(0x0400'001e);

static auto& bg2_rot_scale_dx          = at<uint16_t>(0x0400'0020);
static auto& bg2_rot_scale_dmx         = at<uint16_t>(0x0400'0022);
static auto& bg2_rot_scale_dy          = at<uint16_t>(0x0400'0024);
static auto& bg2_rot_scale_dmy         = at<uint16_t>(0x0400'0026);
static auto& bg2_reference_x           = at<uint32_t>(0x0400'0028);
static auto& bg2_reference_y           = at<uint32_t>(0x0400'002c);

static auto& bg3_rot_scale_dx          = at<uint16_t>(0x0400'0030);
static auto& bg3_rot_scale_dmx         = at<uint16_t>(0x0400'0032);
static auto& bg3_rot_scale_dy          = at<uint16_t>(0x0400'0034);
static auto& bg3_rot_scale_dmy         = at<uint16_t>(0x0400'0036);
static auto& bg3_reference_x           = at<uint32_t>(0x0400'0038);
static auto& bg3_reference_y           = at<uint32_t>(0x0400'003c);

static auto& window0_h                 = at<uint16_t>(0x0400'0040);
static auto& window1_h                 = at<uint16_t>(0x0400'0042);
static auto& window0_v                 = at<uint16_t>(0x0400'0044);
static auto& window1_v                 = at<uint16_t>(0x0400'0046);
static auto& window_inside             = at<uint16_t>(0x0400'0048);
static auto& window_outside            = at<uint16_t>(0x0400'004a);

static auto& mosaic_size               = at<uint16_t>(0x0400'004c);
static auto& effect_control            = at<uint16_t>(0x0400'0050);
static auto& blend_a                   = at<uint8_t>(0x0400'0052);
static auto& blend_b                   = at<uint8_t>(0x0400'0054);
static auto& brightness                = at<uint16_t>(0x0400'0056);

}

/**
 * Sound Registers
 */
namespace sound {

static auto& channel1_sweep            = at<std::bitset<16>>(0x0400'0060);
static auto& channel1_envelope         = at<std::bitset<16>>(0x0400'0062);
static auto& channel1_control          = at<std::bitset<16>>(0x0400'0064);

static auto& channel2_envelope         = at<std::bitset<16>>(0x0400'0068);
static auto& channel2_control          = at<std::bitset<16>>(0x0400'006c);

static auto& channel3_wave_bank        = at<std::bitset<16>>(0x0400'0070);
static auto& channel3_length           = at<std::bitset<16>>(0x0400'0072);
static auto& channel3_control          = at<std::bitset<16>>(0x0400'0074);

static auto& channel4_envelope         = at<std::bitset<16>>(0x0400'0078);
static auto& channel4_noise            = at<std::bitset<16>>(0x0400'007c);

static auto& dmg_control               = at<std::bitset<16>>(0x0400'0080);
static auto& directsound_control       = at<std::bitset<16>>(0x0400'0082);
static auto& status                    = at<std::bitset<16>>(0x0400'0084);

static auto& bias                      = at<std::bitset<16>>(0x0400'0088);

static auto& wave_ram0_l               = at<std::bitset<16>>(0x0400'0090);
static auto& wave_ram0_h               = at<std::bitset<16>>(0x0400'0092);

static auto& wave_ram1_l               = at<std::bitset<16>>(0x0400'0094);
static auto& wave_ram1_h               = at<std::bitset<16>>(0x0400'0096);

static auto& wave_ram2_l               = at<std::bitset<16>>(0x0400'0098);
static auto& wave_ram2_h               = at<std::bitset<16>>(0x0400'009a);

// TODO: Fix data types
static auto& wave_ram3_l               = at<std::bitset<16>>(0x0400'009c);
static auto& wave_ram3_h               = at<std::bitset<16>>(0x0400'009e);

static auto& dsa_fifo_0                = at<uint8_t>(0x0400'00a0);
static auto& dsa_fifo_1                = at<uint8_t>(0x0400'00a1);
static auto& dsa_fifo_2                = at<uint8_t>(0x0400'00a2);
static auto& dsa_fifo_3                = at<uint8_t>(0x0400'00a3);

static auto& dsb_fifo_0                = at<uint8_t>(0x0400'00a4);
static auto& dsb_fifo_1                = at<uint8_t>(0x0400'00a5);
static auto& dsb_fifo_2                = at<uint8_t>(0x0400'00a6);
static auto& dsb_fifo_3                = at<uint8_t>(0x0400'00a7);

}

/**
 * IO Registers
 */
namespace io {

static auto& dma0_source               = at<uint32_t>(0x0400'00b0);
static auto& dma0_destination          = at<uint32_t>(0x0400'00b4);
static auto& dma0_word_coun            = at<uint16_t>(0x0400'00b8);
static auto& dma0_control              = at<uint16_t>(0x0400'00ba);

static auto& dma1_source               = at<uint32_t>(0x0400'00bc);
static auto& dma1_destination          = at<uint32_t>(0x0400'00c0);
static auto& dma1_word_coun            = at<uint16_t>(0x0400'00c4);
static auto& dma1_control              = at<uint16_t>(0x0400'00c6);

static auto& dma2_source               = at<uint32_t>(0x0400'00c8);
static auto& dma2_destination          = at<uint32_t>(0x0400'00cc);
static auto& dma2_word_coun            = at<uint16_t>(0x0400'00d0);
static auto& dma2_control              = at<uint16_t>(0x0400'00d2);

static auto& dma3_source               = at<uint32_t>(0x0400'00d4);
static auto& dma3_destination          = at<uint32_t>(0x0400'00d8);
static auto& dma3_word_coun            = at<uint16_t>(0x0400'00dc);
static auto& dma3_control              = at<uint16_t>(0x0400'00de);

static auto& timer0_counter            = at<uint16_t>(0x0400'0100);
static auto& timer0_control            = at<uint16_t>(0x0400'0102);
static auto& timer1_counter            = at<uint16_t>(0x0400'0104);
static auto& timer1_control            = at<uint16_t>(0x0400'0106);
static auto& timer2_counter            = at<uint16_t>(0x0400'0108);
static auto& timer2_control            = at<uint16_t>(0x0400'010a);
static auto& timer3_counter            = at<uint16_t>(0x0400'010c);
static auto& timer3_control            = at<uint16_t>(0x0400'010e);

static auto& serial_data               = at<uint32_t>(0x0400'0120);
static auto& serial_parent             = at<uint16_t>(0x0400'0120);
static auto& serial_first              = at<uint16_t>(0x0400'0122);
static auto& serial_second             = at<uint16_t>(0x0400'0124);
static auto& serial_third              = at<uint16_t>(0x0400'0126);
static auto& serial_control            = at<uint16_t>(0x0400'0128);
static auto& serial_send_data          = at<uint8_t>(0x0400'012a);

static auto& keypad_status             = at<std::bitset<16>>(0x0400'00130);
static auto& keypad_interrupt          = at<std::bitset<16>>(0x0400'00132);

static auto& serial_mode               = at<std::bitset<16>>(0x0400'00134);
static auto& serial_joy_control        = at<std::bitset<16>>(0x0400'00140);
static auto& serial_joy_receive_data   = at<uint32_t>(0x0400'00150);
static auto& serial_joy_transmit_data  = at<uint32_t>(0x0400'00154);
static auto& serial_joy_receive_status = at<std::bitset<32>>(0x0400'00158);

}

//----------------------------------------------------------------------------
// CPU
//----------------------------------------------------------------------------
namespace cpu {

static auto& interrupt_enable          = at<std::bitset<16>>(0x0400'0200);
static auto& interrupt_request         = at<std::bitset<16>>(0x0400'0202);
static auto& gamepak_wait_control      = at<std::bitset<16>>(0x0400'0204);
static auto& master_enable             = at<std::bitset<16>>(0x0400'0206);

}

}

#endif
