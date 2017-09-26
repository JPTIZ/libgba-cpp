#include "layers.h"

#include "../architecture/registers.h"
#include "../utility.h"

namespace {

using gba::display::BackgroundControl;
using gba::architecture::registers::display::bg_controls;

static auto bg_controls_base = *reinterpret_cast<std::array<BackgroundControl, 4>*>(&bg_controls);

}

BackgroundControl& gba::display::bg_control(gba::display::Layer layer) {
    return bg_controls_base[utils::value_of(layer)];
}
