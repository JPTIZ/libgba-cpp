#ifndef LIBGBACPP_DRIVERS_ARCHITECTURE_REGISTERS_H
#define LIBGBACPP_DRIVERS_ARCHITECTURE_REGISTERS_H

#include <array>
#include <cstdint>
#include <bitset>


/**
 * Elements related to GBA's physical architecture.
 */
namespace gba::architecture {}

/**
 * Registers from GBA architecture.
 */
namespace gba::architecture::registers {

/**
 * Allocates and returns data from a register from a given address.
 *
 * @param address The addres as an unsigned integer value.
 *
 * @tparam T Type to read the register as.
 *
 * @returns Instantiated data in given address.
 */
template <typename T>
inline auto& at(unsigned address) {
    return *new (reinterpret_cast<void*>(address)) T{};
}

template <>
inline auto& at<uint16_t>(unsigned address) {
    return *reinterpret_cast<uint16_t*>(address);
}

/**
 * Display Registers.
 */
namespace display {

/**
 * Display Control Register.
 */
static auto& lcd_control                = at<std::bitset<16>>(0x0400'0000);

/**
 * Green Swap Register (no official documentation).
 */
static auto& green_swap                 = at<std::bitset<16>>(0x0400'0002);

/**
 * Display status register.
 */
static auto& lcd_status                 = at<std::bitset<16>>(0x0400'0004);

/**
 * Number of scanline currently being processed by PPU.
 */
static volatile auto& vcount            = at<uint16_t>(0x0400'0006);

/**
 * BG[0-3] layer control registers.
 *
 * | Bit   | Explanation                                 |
 * |-------|---------------------------------------------|
 * | 0-1   | Priority.                                   |
 * | 2-3   | Character base block.                       |
 * | 4-5   | Unused (must be 0).                         |
 * | 6     | Mosaic enabled.                             |
 * | 7     | Palette depth. 0: 16 colors, 1: 256 colors. |
 * | 8-12  | Screen base block (in units of 2 KB).       |
 * | 13    | Display area overflow method. @see Overflow |
 * | 14-15 | Screen size. @see ScreenSize                |
 */
static auto& bg_controls                = at<std::array<uint16_t, 4>>(0x0400'0008);

/**
 * BG0 layer's reference `X` starting point. Higher values makes the layer
 * seems to have "moved left", while lower values makes the layer seems to have
 * "moved right".
 */
static auto& bg0_x_offset               = at<uint16_t>(0x0400'0010);

/**
 * BG0 layer's reference `Y` starting point. Higher values makes the layer
 * seems to have "moved up", while lower values makes the layer seems to have
 * "moved down".
 */
static auto& bg0_y_offset               = at<uint16_t>(0x0400'0012);

/**
 * BG1 layer's reference `X` starting point. @see bg0_x_offset
 */
static auto& bg1_x_offset               = at<uint16_t>(0x0400'0014);

/**
 * BG1 layer's reference `Y` starting point. @see bg0_y_offset
 */
static auto& bg1_y_offset               = at<uint16_t>(0x0400'0016);

/**
 * BG2 layer's reference `X` starting point. @see bg0_x_offset
 */
static auto& bg2_x_offset               = at<uint16_t>(0x0400'0018);

/**
 * BG2 layer's reference `Y` starting point. @see bg0_y_offset
 */
static auto& bg2_y_offset               = at<uint16_t>(0x0400'001a);

/**
 * BG3 layer's reference `X` starting point. @see bg0_x_offset
 */
static auto& bg3_x_offset               = at<uint16_t>(0x0400'001c);

/**
 * BG3 layer's reference `Y` starting point. @see bg0_y_offset
 */
static auto& bg3_y_offset               = at<uint16_t>(0x0400'001e);

static auto& bg2_rot_scale_dx           = at<uint16_t>(0x0400'0020);
static auto& bg2_rot_scale_dmx          = at<uint16_t>(0x0400'0022);
static auto& bg2_rot_scale_dy           = at<uint16_t>(0x0400'0024);
static auto& bg2_rot_scale_dmy          = at<uint16_t>(0x0400'0026);
static auto& bg2_reference_x            = at<uint32_t>(0x0400'0028);
static auto& bg2_reference_y            = at<uint32_t>(0x0400'002c);

static auto& bg3_rot_scale_dx           = at<uint16_t>(0x0400'0030);
static auto& bg3_rot_scale_dmx          = at<uint16_t>(0x0400'0032);
static auto& bg3_rot_scale_dy           = at<uint16_t>(0x0400'0034);
static auto& bg3_rot_scale_dmy          = at<uint16_t>(0x0400'0036);
static auto& bg3_reference_x            = at<uint32_t>(0x0400'0038);
static auto& bg3_reference_y            = at<uint32_t>(0x0400'003c);

static auto& window0_h                  = at<uint16_t>(0x0400'0040);
static auto& window1_h                  = at<uint16_t>(0x0400'0042);
static auto& window0_v                  = at<uint16_t>(0x0400'0044);
static auto& window1_v                  = at<uint16_t>(0x0400'0046);
static auto& window_inside              = at<uint16_t>(0x0400'0048);
static auto& window_outside             = at<uint16_t>(0x0400'004a);

static auto& mosaic_size                = at<uint16_t>(0x0400'004c);
static auto& effect_control             = at<std::bitset<16>>(0x0400'0050);
static auto& blend_a                    = at<uint8_t>(0x0400'0052);
static auto& blend_b                    = at<uint8_t>(0x0400'0054);
static auto& brightness                 = at<uint16_t>(0x0400'0056);

static auto& bg_palette                 = at<std::array<uint16_t, 256>>(0x0500'0000);
}

/**
 * Sound Registers
 */
namespace sound {

static auto& channel1_sweep             = at<std::bitset<16>>(0x0400'0060);
static auto& channel1_envelope          = at<std::bitset<16>>(0x0400'0062);
static auto& channel1_control           = at<std::bitset<16>>(0x0400'0064);

static auto& channel2_envelope          = at<std::bitset<16>>(0x0400'0068);
static auto& channel2_control           = at<std::bitset<16>>(0x0400'006c);

static auto& channel3_wave_bank         = at<std::bitset<16>>(0x0400'0070);
static auto& channel3_length            = at<std::bitset<16>>(0x0400'0072);
static auto& channel3_control           = at<std::bitset<16>>(0x0400'0074);

static auto& channel4_envelope          = at<std::bitset<16>>(0x0400'0078);
static auto& channel4_noise             = at<std::bitset<16>>(0x0400'007c);

static auto& dmg_control                = at<std::bitset<16>>(0x0400'0080);
static auto& directsound_control        = at<std::bitset<16>>(0x0400'0082);
static auto& status                     = at<std::bitset<16>>(0x0400'0084);

static auto& bias                       = at<std::bitset<16>>(0x0400'0088);

static auto& wave_ram0_l                = at<std::bitset<16>>(0x0400'0090);
static auto& wave_ram0_h                = at<std::bitset<16>>(0x0400'0092);

static auto& wave_ram1_l                = at<std::bitset<16>>(0x0400'0094);
static auto& wave_ram1_h                = at<std::bitset<16>>(0x0400'0096);

static auto& wave_ram2_l                = at<std::bitset<16>>(0x0400'0098);
static auto& wave_ram2_h                = at<std::bitset<16>>(0x0400'009a);

// TODO: Fix data types
static auto& wave_ram3_l                = at<std::bitset<16>>(0x0400'009c);
static auto& wave_ram3_h                = at<std::bitset<16>>(0x0400'009e);

static auto& dsa_fifo_0                 = at<uint8_t>(0x0400'00a0);
static auto& dsa_fifo_1                 = at<uint8_t>(0x0400'00a1);
static auto& dsa_fifo_2                 = at<uint8_t>(0x0400'00a2);
static auto& dsa_fifo_3                 = at<uint8_t>(0x0400'00a3);

static auto& dsb_fifo_0                 = at<uint8_t>(0x0400'00a4);
static auto& dsb_fifo_1                 = at<uint8_t>(0x0400'00a5);
static auto& dsb_fifo_2                 = at<uint8_t>(0x0400'00a6);
static auto& dsb_fifo_3                 = at<uint8_t>(0x0400'00a7);

}

/**
 * IO Registers
 */
namespace io {

static auto& dma0_source                = at<uint32_t>(0x0400'00b0);
static auto& dma0_destination           = at<uint32_t>(0x0400'00b4);
static auto& dma0_word_coun             = at<uint16_t>(0x0400'00b8);
static auto& dma0_control               = at<uint16_t>(0x0400'00ba);

static auto& dma1_source                = at<uint32_t>(0x0400'00bc);
static auto& dma1_destination           = at<uint32_t>(0x0400'00c0);
static auto& dma1_word_coun             = at<uint16_t>(0x0400'00c4);
static auto& dma1_control               = at<uint16_t>(0x0400'00c6);

static auto& dma2_source                = at<uint32_t>(0x0400'00c8);
static auto& dma2_destination           = at<uint32_t>(0x0400'00cc);
static auto& dma2_word_coun             = at<uint16_t>(0x0400'00d0);
static auto& dma2_control               = at<uint16_t>(0x0400'00d2);

static auto& dma3_source                = at<uint32_t>(0x0400'00d4);
static auto& dma3_destination           = at<uint32_t>(0x0400'00d8);
static auto& dma3_word_coun             = at<uint16_t>(0x0400'00dc);
static auto& dma3_control               = at<uint16_t>(0x0400'00de);

static auto& timer0_counter             = at<uint16_t>(0x0400'0100);
static auto& timer0_control             = at<uint16_t>(0x0400'0102);
static auto& timer1_counter             = at<uint16_t>(0x0400'0104);
static auto& timer1_control             = at<uint16_t>(0x0400'0106);
static auto& timer2_counter             = at<uint16_t>(0x0400'0108);
static auto& timer2_control             = at<uint16_t>(0x0400'010a);
static auto& timer3_counter             = at<uint16_t>(0x0400'010c);
static auto& timer3_control             = at<uint16_t>(0x0400'010e);

static auto& serial_data                = at<uint32_t>(0x0400'0120);
static auto& serial_parent              = at<uint16_t>(0x0400'0120);
static auto& serial_first               = at<uint16_t>(0x0400'0122);
static auto& serial_second              = at<uint16_t>(0x0400'0124);
static auto& serial_third               = at<uint16_t>(0x0400'0126);
static auto& serial_control             = at<uint16_t>(0x0400'0128);
static auto& serial_send_data           = at<uint8_t>(0x0400'012a);

static auto& keypad_status              = at<std::bitset<16>>(0x0400'00130);
static auto& keypad_interrupt           = at<std::bitset<16>>(0x0400'00132);

static auto& serial_mode                = at<std::bitset<16>>(0x0400'00134);
static auto& serial_joy_control         = at<std::bitset<16>>(0x0400'00140);
static auto& serial_joy_receive_data    = at<uint32_t>(0x0400'00150);
static auto& serial_joy_transmit_data   = at<uint32_t>(0x0400'00154);
static auto& serial_joy_receive_status  = at<std::bitset<32>>(0x0400'00158);

}

//----------------------------------------------------------------------------
// CPU
//----------------------------------------------------------------------------
namespace cpu {

static auto& interrupt_enable           = at<std::bitset<16>>(0x0400'0200);
static volatile auto& interrupt_request = at<volatile uint16_t>(0x0400'0202);
static auto& gamepak_wait_control       = at<std::bitset<16>>(0x0400'0204);
static auto& master_enable              = at<std::bitset<16>>(0x0400'0208);

}

//----------------------------------------------------------------------------
// BIOS
//----------------------------------------------------------------------------
namespace bios {

static volatile auto& interrupt_check   = at<std::bitset<16>>(0x0300'7ff8);

}

}

#endif
