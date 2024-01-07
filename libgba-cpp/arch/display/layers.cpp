#include <libgba-cpp/arch/display/layers.h>
#include <libgba-cpp/arch/registers.h>
#include <libgba-cpp/utils/general.h>

namespace {

using gba::display::BackgroundControl;
using gba::display::RawPalette;

static auto const bg_address = reinterpret_cast<RawPalette<256>*>(0x0500'0000);
static auto& bg_palette = *new (bg_address) RawPalette<256>{};

} // namespace

BackgroundControl& gba::display::bg_control(gba::display::Layer layer) {
    return *(
        reinterpret_cast<BackgroundControl*>(0x0400'0008) +
        utils::value_of(layer)
    );
}

RawPalette<256>& gba::display::bg_palette() {
    return ::bg_palette;
}
