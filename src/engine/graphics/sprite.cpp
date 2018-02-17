#include <libgba-cpp/engine/graphics/sprite.h>

#include <optional>
#include <utility>

using namespace gba;
using namespace utils;
using namespace std;

namespace {
    using gba::graphics::Sprite;

    struct OAMEntry {
        bitset<16> attr0;
        bitset<16> attr1;
        bitset<16> attr2;
    };

    auto& oam = *new (reinterpret_cast<void*>(0x0700'0000)) array<OAMEntry, 128>{};
    auto oam_map = array<pair<optional<Sprite&>, int>, 128>{};

    /**
     * Finds a place for sprite in OAM.
     */
    void oam_alloc(const Sprite& new_sprite) {
        auto i = 0;
        for (auto entry: oam_map) {
            auto [sprite, _] = entry;
            if (not sprite) {
                entry = {new_sprite, i};
                return;
            }
            ++i;
        }
    }

    /**
     * Frees sprite's place in OAM.
     */
    void oam_free(Sprite& sprite) {
        for (const auto& entry: oam_map) {
            auto [sprite, index] = entry;
            if (sprite) {
                entry = {nullopt, index};
                return;
            }
        }
    }

    void draw(const Sprite& sprite, int i) {
        oam[i].attr0 =
            (sprite.y() & 0b1111111) |
            (sprite.visible() << 9)
            ;
    }
}

Sprite::Sprite(const Bitmap& bitmap, Sprite::Size size):
    bitmap_{bitmap},
    size_{std::move(size)}
{
    oam_alloc(*this);
}

Sprite::~Sprite() {
    oam_free(*this);
}

void graphics::refresh_sprites() {
    for (const auto& entry: oam_map) {
        const auto [sprite, i] = entry;
        draw(sprite, i);
    }
}
