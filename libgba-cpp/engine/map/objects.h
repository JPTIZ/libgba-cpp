#ifndef LIBGBA_ENGINE_MAPOBJECTS_H
#define LIBGBA_ENGINE_MAPOBJECTS_H

#include "libgba-cpp/utils/geometry.h"
namespace gba::map {

/**
 * For bitmaps with a custom drawing routine.
 */
class BitmapModeObject {
    using DrawFunction =
        void (*)(BitmapModeObject const&);

public:
    BitmapModeObject(gba::geometry::Point const& position, gba::geometry::Size size, DrawFunction draw_function):
        _position{position},
        _size{size},
        draw_function{draw_function} {
    }

    auto draw() const -> void {
        draw_function(*this);
    }

    auto position() -> gba::geometry::Point& {
      return _position;
    }

    auto position() const -> gba::geometry::Point const& {
      return _position;
    }

    auto size() const -> gba::geometry::Size const& {
        return _size;
    }

private:
    gba::geometry::Point _position;
    gba::geometry::Size _size;

    DrawFunction draw_function;
};


}

#endif
