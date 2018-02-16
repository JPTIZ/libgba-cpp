#include <libgba-cpp/drivers/display/layers.h>

#include <libgba-cpp/drivers/arch/registers.h>
#include <libgba-cpp/drivers/utility.h>

namespace {

using gba::display::BackgroundControl;
using gba::architecture::registers::display::bg_controls;

}

BackgroundControl& gba::display::bg_control(gba::display::Layer layer) {
    return *(reinterpret_cast<BackgroundControl*>(0x0400'0008) + utils::value_of(layer));
}
