#include <libgba/arch/cpu/interrupts.h>

#include <libgba/arch/registers.h>
#include <libgba/arch/display/control.h>

#include <array>
#include <bitset>

namespace {

using gba::cpu::Interrupt;
using gba::cpu::handler_function_t;

using namespace gba::arch::registers::bios;
using namespace gba::arch::registers::cpu;

auto& main_handler = *reinterpret_cast<handler_function_t*>(0x0300'7ffc);
auto& display_status = *new (reinterpret_cast<void*>(0x0400'0004)) std::bitset<8>{};
auto& vcount_desired = *reinterpret_cast<uint8_t*>(0x0400'0005);

struct Handler {
    Interrupt type;
    handler_function_t function = nullptr;
};

struct Sender {
    uint16_t offset;
    uint8_t bit;
};

auto handlers = std::array<Handler, 14>{};
auto senders = std::array<Sender, 14>{
    Sender
    {0x0004, 3},
    {0x0004, 4},
    {0x0004, 5},
    {0x0102, 6},
    {0x0106, 6},
    {0x010a, 6},
    {0x010e, 6},
    {0x0128, 14},
    {0x00ba, 14},
    {0x00c6, 14},
    {0x00d2, 14},
    {0x00de, 14},
    {0x0132, 14},
    {0x0000, 0},
};

auto& register_at(uint16_t address) {
    return *reinterpret_cast<std::bitset<16>*>(0x0400'0000 + address);
}

void set_interrupt_bit(Handler handler, bool enabled) {
    const auto& sender = senders[utils::value_of(handler.type)];
    register_at(sender.offset)[sender.bit] = enabled;
}

void fit_handler(Interrupt which, handler_function_t function) {
    auto handler = Handler{which, function};
    for (auto& handler_ : handlers) {
        if (handler_.function == nullptr or handler_.type == which) {
            handler_ = handler;
            set_interrupt_bit(handler, true);
            return;
        }
    }
}

void remove_handler(Interrupt which) {
    auto i = 0;
    for (auto& handler : handlers) {
        if (handler.type == which) {
            set_interrupt_bit(handler, false);
            for (auto j = i; j < handlers.size() - 1; ++j) {
                handlers[j] = handlers[j + 1];
            }
            handlers[handlers.size() - 1] = {which, nullptr};
        }
    }
}

auto find_handler(uint16_t ie_if) {
    for (const auto& handler: handlers) {
        if (utils::value_of(handler.type) & ie_if) {
            return handler;
        }
    }
    return Handler{Interrupt::VBLANK, nullptr};
}

}

namespace gba {

void cpu::interrupts_enabled(bool enabled) {
    master_enable = enabled;
}

void cpu::main_interrupt_switchboard() {
    /*
    auto ie_reg = interrupt_enable;

    auto if_reg = interrupt_request;
    auto ie_if = ie_reg & if_reg;

    interrupt_request = ie_if;
    interrupt_check = ie_if;

    const auto& handler = find_handler(interrupt_request);

    if (handler.function == nullptr) {
        return;
    }

    auto old_master = master_enable;
    master_enable = false;
    interrupt_enable &= ~ie_if;

    handler.function();

    interrupt_enable = ie_reg;
    master_enable = true;
    */
}

void cpu::vblank_interrupt(bool enabled) {
    display_status[0] = enabled;
    interrupt_enable[0] = enabled;
}

void cpu::hblank_interrupt(bool enabled) {
    display_status[1] = enabled;
    interrupt_enable[1] = enabled;
}

void cpu::vcount_interrupt(bool enabled, unsigned value) {
    vcount_desired = value;
    display_status[2] = enabled;
    interrupt_enable[2] = enabled;
}

void cpu::serial_interrupt(bool enabled) {
    interrupt_enable[7] = enabled;
}

void cpu::keypad_interrupt(bool enabled) {
    interrupt_enable[12] = enabled;
}

void cpu::cartridge_interrupt(bool enabled) {
    interrupt_enable[13] = enabled;
}

void cpu::interrupt_handler(handler_function_t function) {
    main_handler = function;
}

/**
 * If interrupt already has a handler, replace.
 * Else, replace first empty handler.
 */
void cpu::set_handler(Interrupt which, handler_function_t function) {
    interrupts_enabled(false);
    fit_handler(which, function);
    interrupts_enabled(true);
}

void cpu::unset_handler(Interrupt which) {
    interrupts_enabled(false);
    remove_handler(which);
    interrupts_enabled(true);
}

void cpu::clear_handlers() {
    interrupts_enabled(false);
    remove_handler(Interrupt::VBLANK);
    remove_handler(Interrupt::HBLANK);
    remove_handler(Interrupt::VCOUNT);
    remove_handler(Interrupt::TIMER0);
    remove_handler(Interrupt::TIMER1);
    remove_handler(Interrupt::TIMER2);
    remove_handler(Interrupt::TIMER3);
    remove_handler(Interrupt::SERIAL);
    remove_handler(Interrupt::DMA0);
    remove_handler(Interrupt::DMA1);
    remove_handler(Interrupt::DMA2);
    remove_handler(Interrupt::DMA3);
    remove_handler(Interrupt::KEYPAD);
    remove_handler(Interrupt::CARTRIDGE);
    interrupts_enabled(true);
}

void cpu::halt() {
    asm(
        "swi %0"
        : // output
        : "i" (4)
        : "r0", "r1", "r2", "r3"
    );
}

}
