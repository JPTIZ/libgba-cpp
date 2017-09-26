#ifndef GBA_DRIVERS_CPU_INTERRUPTS_H
#define GBA_DRIVERS_CPU_INTERRUPTS_H

namespace gba::cpu {

using handler_function_t = void(*)();

/**
 * Interrupt type.
 */
enum class Interrupt {
    VBLANK,
    HBLANK,
    VCOUNT,
    TIMER0,
    TIMER1,
    TIMER2,
    TIMER3,
    SERIAL,
    DMA0,
    DMA1,
    DMA2,
    DMA3,
    KEYPAD,
    CARTRIDGE,
};

/**
 * Interrupt switchboard.
 */
void __attribute__((interrupt ("IRQ"))) __attribute__((section(".iwram"))) main_interrupt_switchboard();

/**
 * Enables/disables hardware interrupts.
 */
void interrupts_enabled(bool flag);

/**
 * Enables/disables VBlank Interrupt.
 *
 * Raised when PPU reaches VBlank.
 */
void vblank_interrupt(bool enabled);

/**
 * Enables/disables HBlank Interrupt.
 *
 * Raised when PPU reaches HBlank.
 */
void hblank_interrupt(bool enabled);

/**
 * Enables/disables VCount Interrupt.
 *
 * Raised when PPU reaches selected value.
 *
 * @param value Scanline number to raise interrupt.
 */
void vcount_interrupt(bool enabled, unsigned value=0);

/**
 * Enables/disables Serial Interrupt.
 *
 * Raised when serial port finishes its operation.
 */
void serial_interrupt(bool enabled);

/**
 * Enables/disables Keypad Interrupt.
 *
 * Raised when player presses a key.
 */
void keypad_interrupt(bool enabled);

/**
 * Enables/disables Cartridge Interrupt.
 *
 * Raised when cartridge is removed.
 */
void cartridge_interrupt(bool enabled);

/**
 * Puts CPU to sleep.
 */
void halt();

void interrupt_handler();
void interrupt_handler(handler_function_t);
void set_handler(Interrupt, handler_function_t);
void unset_handler(Interrupt);
void clear_handlers();

inline void no_action() {
    return;
}

inline void setup_interrupts() {
    interrupts_enabled(true);
    interrupt_handler(main_interrupt_switchboard);
    set_handler(Interrupt::VBLANK, no_action);
}

}

#endif
