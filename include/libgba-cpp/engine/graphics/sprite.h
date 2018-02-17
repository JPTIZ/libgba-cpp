#ifndef LIBGBA_CPP_ENGINE_GRAPHICS_SPRITE_H
#define LIBGBA_CPP_ENGINE_GRAPHICS_SPRITE_H

#include <utility>

#include <libgba-cpp/drivers/geometry.h>
#include <libgba-cpp/engine/graphics/bitmap.h>


namespace gba::graphics {

/**
 * A visible sprite in VRAM.
 */
class Sprite {
    using Point = geometry::Point;
    using Size = geometry::Size;
public:
    Sprite(const Bitmap& bitmap, Size size);
    ~Sprite();

    auto x() const {
        return pos_.x;
    }

    auto y() const {
        return pos_.y;
    }

    /**
     * Sprite's width in pixels.
     */
    auto width() const {
        return size_.width;
    }

    /**
     * Sprite's height in pixels.
     */
    auto height() const {
        return size_.height;
    }

    /**
     * Sprite's current location on map.
     */
    const auto& pos() const {
        return pos_;
    }

    /**
     * Sprite's size in pixels.
     */
    const auto& size() const {
        return size_;
    }

    /**
     * Moves sprite to specific location on map.
     */
    void move(int x, int y) {
        pos_ = {x, y};
    }

    void move(const Point& p) {
        move(p.x, p.y);
    }

    /**
     * Moves sprite relative to current location.
     */
    void offset(int x, int y) {
        pos_.x += x;
        pos_.y += y;
    }

    void offset(const Point& p) {
        offset(p.x, p.y);
    }

    auto visible() const {
        return visible_;
    }

private:
    const Bitmap& bitmap_;
    Point pos_ = {0, 0};
    Size size_;
    bool visible_ = true;
};

void refresh_sprites();

}

#endif
