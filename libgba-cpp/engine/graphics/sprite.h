#ifndef LIBGBA_CPP_ENGINE_GRAPHICS_SPRITE_H
#define LIBGBA_CPP_ENGINE_GRAPHICS_SPRITE_H

#include <optional>

#include <libgba-cpp/arch/display/objects.h>
#include <libgba-cpp/engine/graphics/tilemap.h>

namespace gba::graphics {
    enum class BitmapShape {
        SQUARE_8x8,
        SQUARE_16x16,
        SQUARE_32x32,
        SQUARE_64x64,

        VERTICAL_8x16,
        VERTICAL_8x32,
        VERTICAL_16x32,
        VERTICAL_32x64,

        HORIZONTAL_16x8,
        HORIZONTAL_32x8,
        HORIZONTAL_32x16,
        HORIZONTAL_64x32,
    };

    inline auto oam_size(BitmapShape const& shape) -> gba::display::ObjectSize {
        switch (shape) {
            default:
            case BitmapShape::SQUARE_8x8:
            case BitmapShape::VERTICAL_8x16:
            case BitmapShape::HORIZONTAL_16x8:
                return gba::display::ObjectSize::TINY;
            case BitmapShape::SQUARE_16x16:
            case BitmapShape::VERTICAL_8x32:
            case BitmapShape::HORIZONTAL_32x8:
                return gba::display::ObjectSize::SMALL;
            case BitmapShape::SQUARE_32x32:
            case BitmapShape::VERTICAL_16x32:
            case BitmapShape::HORIZONTAL_32x16:
                return gba::display::ObjectSize::MEDIUM;
            case BitmapShape::SQUARE_64x64:
            case BitmapShape::VERTICAL_32x64:
            case BitmapShape::HORIZONTAL_64x32:
                return gba::display::ObjectSize::BIG;
        }
    }

    inline auto oam_shape(BitmapShape const& shape) -> gba::display::ObjectShape {
        switch (shape) {
            default:
            case BitmapShape::SQUARE_8x8:
            case BitmapShape::SQUARE_16x16:
            case BitmapShape::SQUARE_32x32:
            case BitmapShape::SQUARE_64x64:
                return gba::display::ObjectShape::SQUARE;
            case BitmapShape::VERTICAL_8x16:
            case BitmapShape::VERTICAL_8x32:
            case BitmapShape::VERTICAL_16x32:
            case BitmapShape::VERTICAL_32x64:
                return gba::display::ObjectShape::VERTICAL;
            case BitmapShape::HORIZONTAL_16x8:
            case BitmapShape::HORIZONTAL_32x8:
            case BitmapShape::HORIZONTAL_32x16:
            case BitmapShape::HORIZONTAL_64x32:
                return gba::display::ObjectShape::HORIZONTAL;
        }
    }

    struct Bitmap {
        Tileset tiles;
        BitmapShape shape;
        std::optional<int> base_tile_index = {};

        auto add_to_screen(int base_tile_index) -> void {
            if (this->base_tile_index) {
                return;
            }

            this->base_tile_index = base_tile_index;

            for (auto i = 0u; i < tiles.length(); ++i) {
                gba::display::sprite_tile(i + base_tile_index) = tiles[i];
            }
        }
    };

    struct Sprite {
        Bitmap bitmap;
        gba::geometry::Point pos;
        gba::geometry::Point offset = {0, 0};
        bool visible = true;
        std::optional<std::reference_wrapper<gba::display::OAMEntry>> oam_entry = {};

        auto add_to_screen(int oam_index, int base_tile_index) -> void {
            if (oam_entry) {
                return;
            }

            this->oam_entry = gba::display::oam_entry(oam_index);
            auto& oam_entry = this->oam_entry.value().get();
            oam_entry.base_tile(base_tile_index);
            oam_entry.size(oam_size(bitmap.shape));
            oam_entry.shape(oam_shape(bitmap.shape));

            bitmap.add_to_screen(base_tile_index);
        }

        auto update() -> void {
            if (not oam_entry) {
                return;
            }

            auto& entry = oam_entry.value().get();
            entry.set_x(pos.x + offset.x);
            entry.set_y(pos.y + offset.y);
            entry.visible(visible);
        }
    };
}

#endif
