#include <libgba-cpp/arch/display/layers.h>
#include <libgba-cpp/arch/display/video.h>
#include <libgba-cpp/engine/graphics.h>
#include <libgba-cpp/engine/input.h>
#include <libgba-cpp/engine/map/objects.h>
#include <libgba-cpp/utils/geometry.h>

#include "libgba-cpp/arch/display/objects.h"

namespace test {

constexpr auto WHITE = gba::display::Color{31, 31, 31};
constexpr auto RED = gba::display::Color{31, 0, 0};
constexpr auto GREEN = gba::display::Color{0, 15, 0};

const auto screen_obj_palette = gba::graphics::Palette{
    std::array<gba::display::Color, 4>{gba::display::Color{}, WHITE, RED, GREEN}
};

// clang-format off

const std::array<gba::display::Color, 2> raw_sample_palette = {
    gba::display::Color
    { 0,  0,  0}, {31, 31, 31},
};

const std::array<uint16_t, 32*32> raw_tileset = {
    /*
    1, 2, 3, 4, 5, 6, 7, 8,         9,10,11,12,13,14,15,16,        17,18,19,20,21,22,23,24,        25,26,27,28,29,30,31,32,
    */
    /*  1 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /*  2 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /*  3 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /*  4 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /*  5 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /*  6 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /*  7 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /*  8 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /*  9 */ /* -------------------------------------------------------------------------------------------------------- */
    /* 10 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 11 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 12 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 13 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 14 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 15 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 16 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 17 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 18 */ /* -------------------------------------------------------------------------------------------------------- */
    /* 19 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 20 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 21 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 22 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 1, 2, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 23 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 24 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 25 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 26 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 27 */ /* -------------------------------------------------------------------------------------------------------- */
    /* 28 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 2, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 29 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 2, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 20 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 2, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 31 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 2, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 32 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 2, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 33 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 2, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 34 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 2, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 35 */ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, /**/ 2, 0, 0, 0, 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0,
};

const std::array<gba::display::map::Tile, 256> sample_tiles = {
    gba::display::map::Tile{{
        0x0, 0x0,
        0x0, 0x0,
        0x0, 0x0,
        0x0, 0x0,
    }},
    gba::display::map::Tile{{
        0x0, 0x0,
        0x0, 0x0,
        0x0, 0x0,
        0x0, 0x0,
    }},
    gba::display::map::Tile{{
        0x00000000, 0x01000000,
        0x00000000, 0x01000000,
        0x00000000, 0x01000000,
        0x00000000, 0x01000000,
    }},
    gba::display::map::Tile{{
        0x00000000, 0x01000000,
        0x00000000, 0x01000000,
        0x00000000, 0x01000000,
        0x00000000, 0x01000000,
    }},
    gba::display::map::Tile{{
        0x00000001, 0x00000000,
        0x00000001, 0x00000000,
        0x00000001, 0x00000000,
        0x00000001, 0x00000000,
    }},
    gba::display::map::Tile{{
        0x00000001, 0x00000000,
        0x00000001, 0x00000000,
        0x00000001, 0x00000000,
        0x00000001, 0x00000000,
    }},
};

// clang-format on

constexpr auto sample_palette = gba::graphics::Palette{raw_sample_palette};
const auto sample_tileset =
    gba::graphics::Tileset{sample_palette, sample_tiles};
const auto sample_tilemap = gba::graphics::Tilemap{raw_tileset};
const auto null_tilemap = gba::graphics::Tilemap{gba::graphics::null_tilemap};

}

constexpr auto PLAYER_WIDTH = 4;
constexpr auto PLAYER_HEIGHT = 16;
constexpr auto LIFE_SIZE = 8;
constexpr auto MAX_LIVES = 3;

constexpr auto SCREEN_SIZE = gba::geometry::Size{
    gba::display::mode3::screen_width,
    gba::display::mode3::screen_height,
};

struct Ball {
    gba::graphics::Sprite sprite;
    gba::geometry::Point speed;
};

struct Player {
    gba::graphics::Sprite sprite;
    gba::geometry::Point speed;
    int lives;

    auto move() -> void {
        sprite.pos = {
            .x = this->sprite.pos.x + speed.x,
            .y = this->sprite.pos.y + speed.y,
        };
    }
};

auto create_lives_sprites(gba::geometry::Point const& origin, int oam_start)
    -> void {
    auto sprite_pos = origin;
    for (auto i = 0; i < MAX_LIVES; ++i) {
        auto& oam_entry = gba::display::oam_entry(oam_start + i);
        oam_entry.set_x(sprite_pos.x);
        oam_entry.set_y(sprite_pos.y);
        oam_entry.size(gba::display::ObjectSize::TINY);
        oam_entry.base_tile(4);
        sprite_pos.x += LIFE_SIZE;
    }
}

auto update_player_lives(int lives, int oam_start) -> void {
    for (auto i = 0; i < lives; ++i) {
        gba::display::oam_entry(oam_start + i).base_tile(4);
    }
    for (auto i = lives; i < MAX_LIVES; ++i) {
        gba::display::oam_entry(oam_start + i).base_tile(5);
    }
}

auto collides(Ball const& ball, gba::geometry::Rect const& hitbox) {
    auto [ball_x, ball_y] = ball.sprite.pos;
    return (
        ball_x >= hitbox.x and ball_y >= hitbox.y and
        ball_x <= hitbox.x + hitbox.width and ball_y <= hitbox.y + hitbox.height
    );
}

struct MatchScreen {

    const gba::graphics::Bitmap ball_bitmap = gba::graphics::Bitmap{
        .tiles =
            gba::graphics::Tileset{
                test::screen_obj_palette,
                std::array<gba::display::map::Tile, 1>{
                    gba::display::map::Tile{{
                        0x00000000,
                        0x00000000,
                        0x00000000,
                        0x00011000,
                        0x00011000,
                        0x00000000,
                        0x00000000,
                        0x00000000,
                    }},
                },
            },
        .shape = gba::graphics::BitmapShape::SQUARE_8x8,
    };

    const gba::graphics::Bitmap player_bitmap = gba::graphics::Bitmap{
        .tiles =
            gba::graphics::Tileset{
                test::screen_obj_palette,
                std::array<gba::display::map::Tile, 2>{
                    gba::display::map::Tile{{
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                    }},
                    gba::display::map::Tile{{
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                        0x00001111,
                    }},
                },
            },
        .shape = gba::graphics::BitmapShape::VERTICAL_8x16,
    };
    bool game_running = false;

    Ball ball = {
        .sprite = gba::graphics::Sprite{
            .bitmap = ball_bitmap,
            .pos =
                {
                    .x = SCREEN_SIZE.width / 2 - 1,
                    .y = (SCREEN_SIZE.height / 2) % SCREEN_SIZE.height,
                },
            .offset = {-2, -2},
        },
        .speed = {-2, -2},
    };

    std::array<Player, 2> players = {
        Player{
            .sprite =
                gba::graphics::Sprite{
                    .bitmap = player_bitmap,
                    .pos = {0, 60},
                },
            .speed = {0, 0},
            .lives = 3,
        },
        Player{
            .sprite =
                gba::graphics::Sprite{
                    .bitmap = player_bitmap,
                    .pos = {SCREEN_SIZE.width - PLAYER_WIDTH - 1, 60},
                },
            .speed = {0, -2},
            .lives = 3
        },
    };

    auto start() -> void {
        using gba::geometry::Point;
        using namespace gba::display;

        const auto map = gba::graphics::Map{
            test::sample_tileset,
            test::sample_tilemap,
            gba::graphics::null_tilemap,
            gba::graphics::null_tilemap,
            gba::graphics::null_tilemap,
            gba::graphics::MapSize::TEXT_256X256
        };

        gba::display::force_blank(true);

        change_mode(Mode::MODE0);
        layer_visible(Layer::BG1);
        layer_visible(Layer::OBJ);

        auto& ball_oam_entry = gba::display::oam_entry(2);
        ball_oam_entry.base_tile(1);

        players[0].sprite.add_to_screen(0, 2);
        players[1].sprite.add_to_screen(1, 2);
        ball.sprite.add_to_screen(2, 1);

        gba::display::obj_palette()[1] = test::WHITE;
        gba::display::obj_palette()[2] = test::RED;
        gba::display::obj_palette()[3] = test::GREEN;

        gba::graphics::load_map(map);

        gba::display::sprite_tile(4) = gba::display::map::Tile{{
            0x00000000,
            0x00000000,
            0x00000000,
            0x33333333,
            0x33333333,
            0x00000000,
            0x00000000,
            0x00000000,
        }};

        gba::display::sprite_tile(5) = gba::display::map::Tile{{
            0x20000002,
            0x02000020,
            0x00200200,
            0x00022000,
            0x00022000,
            0x00200200,
            0x02000020,
            0x20000002,
        }};

        create_lives_sprites(
            gba::geometry::Point{
                SCREEN_SIZE.width / 2 - LIFE_SIZE * (MAX_LIVES + 1),
                5
            },
            3
        );
        create_lives_sprites(
            gba::geometry::Point{SCREEN_SIZE.width / 2 + LIFE_SIZE, 5},
            6
        );

        gba::display::force_blank(false);
    }

    auto new_match(int seed) -> void {
        auto ball_hor_dir = seed % 2 == 0 ? -1 : 1;
        auto ball_ver_dir = (seed / 3) % 2 == 0 ? -1 : 1;
        auto ball_h_speed = (seed / 17) % 2 + 1;
        auto ball_v_speed = (seed / 7) % 3 + 1;

        auto ball_dir = gba::geometry::Point{
            ball_hor_dir * ball_h_speed,
            ball_ver_dir * ball_v_speed
        };

        ball.sprite.pos =
                {SCREEN_SIZE.width / 2 - 1,
                 (SCREEN_SIZE.height / 2 + seed) % SCREEN_SIZE.height};
        ball.speed = ball_dir;

        update_player_lives(players[0].lives, 3);
        update_player_lives(players[1].lives, 6);
    }

    auto update() -> void {
        if (game_running) {
            game_loop();
        } else if (gba::input::pressing(gba::input::Key::START)) {
            game_running = true;
            players[0].lives = MAX_LIVES;
            players[1].lives = MAX_LIVES;
            new_match(gba::utils::random());
        }
    }

    auto game_loop() -> void {
        using gba::geometry::Rect;

        auto seed = gba::utils::random();
        // Screen size is 240x160, so value ranges [0..239, 0..159].
        // For the upper index we must consider that the ball starts -2 pixels
        // from it, because its reference is top-left and the ball has a size
        // of 2x2.
        if (ball.sprite.pos.x <= 0 or ball.sprite.pos.x >= SCREEN_SIZE.width - 3) {
            ball.speed.x *= -1;
        }

        if (ball.sprite.pos.y <= 0 or ball.sprite.pos.y >= SCREEN_SIZE.height - 3) {
            ball.speed.y *= -1;
        }
        ball.sprite.pos.x += ball.speed.x;
        ball.sprite.pos.y += ball.speed.y;

        if (ball.sprite.pos.x >= SCREEN_SIZE.width - 3) {
            players[1].lives -= 1;
            update_player_lives(players[1].lives, 6);
            new_match(seed);
        } else if (ball.sprite.pos.x == 0) {
            players[0].lives -= 1;
            update_player_lives(players[0].lives, 3);
            new_match(seed);
        }

        if (players[0].lives == 0 or players[1].lives == 0) {
            game_running = false;
        }

        // Update opponent position
        if (players[1].sprite.pos.y == 0 or
            players[1].sprite.pos.y >= 159 - PLAYER_HEIGHT) {
            players[1].speed.y *= -1;
        }

        using gba::input::Key;

        if (gba::input::pressing(Key::UP)) {
            players[0].speed.y = -2;
        } else if (gba::input::pressing(Key::DOWN)) {
            players[0].speed.y = 2;
        } else {
            players[0].speed.y = 0;
        }

        if (gba::input::pressing(Key::A)) {
            ball.sprite.pos.x = 15;
            ball.sprite.pos.y = 15;
        }

        for (auto&& player : players) {
            player.move();
            if (player.sprite.pos.y + PLAYER_HEIGHT > SCREEN_SIZE.height) {
                player.sprite.pos.y = SCREEN_SIZE.height - PLAYER_HEIGHT;
            }
            if (player.sprite.pos.y < 0) {
                player.sprite.pos.y = 0;
            }
        }

        auto [p0, p1] = std::array{
            players[0].sprite.pos,
            players[1].sprite.pos,
        };

        auto players_hitbox = std::array{
            Rect{-10, p0.y, 10 + PLAYER_WIDTH, PLAYER_HEIGHT},
            Rect{
                SCREEN_SIZE.width - PLAYER_WIDTH,
                p1.y,
                10 + PLAYER_WIDTH,
                PLAYER_HEIGHT
            },
        };

        auto collides_with_p0 = collides(ball, players_hitbox[0]);
        auto collides_with_p1 = collides(ball, players_hitbox[1]);

        if (collides_with_p0) {
            ball.speed.x *= -1;
            ball.speed.y += players[0].speed.y;
        }

        if (collides_with_p1) {
            ball.speed.x *= -1;
            ball.speed.y += players[1].speed.y;
        }
    }

    auto draw() -> void {
        // No additional steps are needed since all graphics updated in this
        // screen are sprites handled through hardware.
        gba::display::vsync();

        ball.sprite.update();
        for (auto&& player : players) {
            player.sprite.update();
        }
    }

    auto post_update() -> void {
    }
};

int main() {
    gba::display::object_mapping(gba::display::ObjectMapping::MAP_ARRAY);

    auto screen = MatchScreen{};

    screen.start();
    while (true) {
        screen.update();
        screen.draw();
    }
}
