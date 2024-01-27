#include <libgba-cpp/arch/display/objects.h>
#include <libgba-cpp/arch/display/tilemap.h>

using gba::display::RawPalette;

namespace {

static auto const obj_palette_address =
    reinterpret_cast<RawPalette<256>*>(0x0500'0200);
static auto& obj_palette = *new (obj_palette_address) RawPalette<256>{};

static auto& oam = *new (reinterpret_cast<void*>(0x0700'0000))
                       std::array<gba::display::OAMEntry, 128>{};
static auto& sprite_tiles = *new (reinterpret_cast<void*>(0x0601'0000)) std::array<gba::display::map::Tile, 256>{};
// auto oam_map = array<pair<optional<Sprite&>, int>, 128>{};

} // namespace

auto gba::display::obj_palette() -> RawPalette<256>& {
    return ::obj_palette;
}

auto gba::display::oam_entry(int index) -> OAMEntry& {
    return ::oam[index];
}

auto gba::display::sprite_tile(int index) -> gba::display::map::Tile& {
    return sprite_tiles[index];
};
