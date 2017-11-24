#ifndef ${namespace.upper()}_MAPS_${name.upper()}_H
#define ${namespace.upper()}_MAPS_${name.upper()}_H

#include <array>

#include <engine/graphics/tilemap.h>
#include <engine/graphics/palette.h>

namespace ${namespace}::maps {

extern const gba::graphics::Palette ${name}_palette;
extern const gba::graphics::Tileset ${name}_tileset;

}

#endif
