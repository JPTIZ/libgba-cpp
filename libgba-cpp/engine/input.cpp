#include <libgba-cpp/arch/registers.h>
#include <libgba-cpp/engine/input.h>
#include <libgba-cpp/utils/general.h>

auto gba::input::pressing(Key key) -> bool {
    auto index = static_cast<std::size_t>(utils::value_of(key));
    //return (*reinterpret_cast<std::uint16_t*>(0x0400'0130)) & (1 << index);
    return not arch::registers::io::keypad_status[index];
}
