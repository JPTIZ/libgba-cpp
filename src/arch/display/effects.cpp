#include <libgba-cpp/arch/display/effects.h>

#include <libgba-cpp/arch/registers.h>


namespace {

using namespace gba::arch::registers::display;
auto mosaic_data = uint16_t{0u};

}


namespace gba {

void display::first_target(Layer layer, bool enabled) {
    effect_control[utils::value_of(layer)] = enabled;
}

void display::backdrop_first_target(bool enabled) {
    effect_control[5] = enabled;
}

void display::second_target(Layer layer, bool enabled) {
    effect_control[utils::value_of(layer) + 8] = enabled;
}

void display::backdrop_second_target(bool enabled) {
    effect_control[13] = enabled;
}

void display::select(SpecialEffect effect) {
    effect_control = (effect_control.to_ulong() & ~(0b11u << 6)) | ((utils::value_of(effect) & 0b11u) << 6);
}

void display::mosaic_bg_level(unsigned width, unsigned height) {
    mosaic_data = (mosaic_data & 0b11111111u) & (width | (height << 4));
    mosaic_size = mosaic_data;
}

void display::mosaic_obj_level(unsigned width, unsigned height) {
    mosaic_data = (mosaic_data & (0b11111111u << 8)) & ((width | (height << 4)) << 8);
    mosaic_size = mosaic_data;
}

}

