#ifndef LIBGBA_CPP_DRIVERS_GEOMETRY_H
#define LIBGBA_CPP_DRIVERS_GEOMETRY_H

namespace gba::geometry {

struct Point {
    int x;
    int y;
};

struct Size {
    int width;
    int height;
};

struct Rect {
    int x;
    int y;
    int width;
    int height;

    auto top_left() const {
        return Point{x, y};
    }

    auto top_right() const {
        return Point{x + width, y};
    }

    auto bottom_left() const {
        return Point{x, y + height};
    }

    auto bottom_right() const {
        return Point{x + width, y + height};
    }

    auto size() const {
        return Size{width, height};
    }
};

}

#endif
