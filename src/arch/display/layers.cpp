#include <libgba-cpp/arch/display/layers.h>

#include <libgba-cpp/arch/registers.h>
#include <libgba-cpp/utils/general.h>

namespace {

using gba::display::BackgroundControl;
using gba::arch::registers::display::bg_controls;

}

BackgroundControl& gba::display::bg_control(gba::display::Layer layer) {
    return *(reinterpret_cast<BackgroundControl*>(0x0400'0008) + utils::value_of(layer));
}
