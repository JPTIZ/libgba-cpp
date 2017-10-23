#include <drivers/display/tilemap.h>

namespace {

using namespace gba::display;
using map::Tile;

static auto& tiles = *new (reinterpret_cast<void*>(0x0600'0000)) std::array<Tile, 0x40>{};
static auto& tilemap = *new (end(tiles)) std::array<std::uint16_t, 1024>{};

}

namespace gba::display {

std::array<Tile, 0x40>& map::tileset() {
    return tiles;
}

std::array<uint16_t, 1024>& map::tilemap() {
    return ::tilemap;
}

}
