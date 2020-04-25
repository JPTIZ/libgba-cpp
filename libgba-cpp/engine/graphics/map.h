#ifndef LIBGBA_ENGINE_MAP_H
#define LIBGBA_ENGINE_MAP_H

#include <libgba-cpp/arch/display/layers.h>
#include "tilemap.h"

namespace gba::graphics {

using gba::display::MapSize;

class Map {
public:
    Map(MapSize size,
        const Tileset& tileset,
        const Tilemap& tilemap):
        size_{size},
        tileset_{tileset},
        tilemap_{tilemap}
    {}

    const auto tileset() const {
        return tileset_;
    }

    const auto tilemap() const {
        return tilemap_;
    }

    const auto size() const {
        return size_;
    }

    const auto width() const {
        return gba::display::extract_size(size_).width;
    }

    const auto height() const {
        return gba::display::extract_size(size_).height;
    }

private:
    const MapSize size_;
    const Tileset& tileset_;
    const Tilemap& tilemap_;
};

}

#endif
