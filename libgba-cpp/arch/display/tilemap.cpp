#include <libgba-cpp/arch/display/tilemap.h>

namespace {

using namespace gba::display;
using map::Tile;

static auto& tiles = *reinterpret_cast<std::array<Tile, 0x40>*>(0x0600'0000);
static auto& tilemap = *reinterpret_cast<std::array<std::uint16_t, 0x9000>*>(tiles.end());

}

namespace gba::display {

std::array<Tile, 0x40>& map::tileset() {
    return tiles;
}

std::array<uint16_t, 0x9000>& map::tilemap() {
    return ::tilemap;
}

}
