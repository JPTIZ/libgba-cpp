#ifndef GBA_DRIVERS_CPU_INTERRUPTS_H
#define GBA_DRIVERS_CPU_INTERRUPTS_H

namespace gba::cpu {

using handler_function_t = void(*)();

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

void main_interrupt_switchboard();
void interrupts_enabled(bool flag);
void vblank_interrupt(bool enabled);
void hblank_interrupt(bool enabled);
void vcount_interrupt(bool enabled, unsigned value=0);

void serial_interrupt(bool enabled);
void keypad_interrupt(bool enabled);
void cartridge_interrupt(bool enabled);

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
