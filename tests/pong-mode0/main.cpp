#include <libgba-cpp/arch/display/layers.h>
#include <libgba-cpp/arch/display/video.h>
#include <libgba-cpp/engine/graphics/tilemap.h>
#include <libgba-cpp/engine/input.h>
#include <libgba-cpp/engine/map/objects.h>
#include <libgba-cpp/utils/geometry.h>

#include "libgba-cpp/arch/display/objects.h"

namespace test {

// clang-format off

const std::array<gba::graphics::Color, 2> raw_sample_palette = {
    gba::graphics::Color
    { 0,  0,  0}, {31, 31, 31},
};

const std::array<uint16_t, 32*32> raw_tileset = {
    /*
    1..8                            9..16                           17..24                          25..32
    1, 2, 3, 4, 5, 6, 7, 8,         1, 2, 3, 4, 5, 6, 7, 8,         1, 2, 3, 4, 5, 6, 7, 8,         1, 2, 3, 4, 5, 6, 7, 8,
    */
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    /* ------------------------+-------------------------------+-------------------------------+------------------------ */
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    /* ------------------------+-------------------------------+-------------------------------+------------------------ */
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 1, 2, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    /* ------------------------+-------------------------------+-------------------------------+------------------------ */
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 2, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 2, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 2, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 2, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 2, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 2, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 2, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0, /* | */ 2, 0, 0, 0, 0, 0, 0, 0, /* | */ 0, 0, 0, 0, 0, 0, 0, 0,
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

const auto sample_palette = gba::graphics::Palette{raw_sample_palette};
const auto sample_tileset =
    gba::graphics::Tileset{sample_palette, sample_tiles};
const auto sample_tilemap = gba::graphics::Tilemap{raw_tileset};
const auto null_tilemap = gba::graphics::Tilemap{gba::graphics::null_tilemap};

} // namespace test

const static auto WHITE = gba::display::Color{31, 31, 31};
const static auto BLACK = gba::display::Color{0, 0, 0};
const static auto RED = gba::display::Color{31, 0, 0};
const static auto GREEN = gba::display::Color{0, 15, 0};

constexpr auto PLAYER_WIDTH = 4;
constexpr auto PLAYER_HEIGHT = 16;
constexpr auto LIFE_SIZE = 8;
constexpr auto MAX_LIVES = 3;

constexpr auto SCREEN_SIZE = gba::geometry::Size{
    gba::display::mode3::screen_width,
    gba::display::mode3::screen_height,
};

struct Ball {
    int oam_index;
    gba::geometry::Point position;
    gba::geometry::Point speed;
};

struct Player {
    int oam_index;
    gba::geometry::Point position;
    gba::geometry::Point speed;
    int lives;

    auto move() -> void {
        position = {
            .x = this->position.x + speed.x,
            .y = this->position.y + speed.y,
        };
        auto& entry = gba::display::oam_entry(oam_index);
        entry.set_x(position.x);
        entry.set_y(position.y);
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
        oam_entry.base_tile(3);
        sprite_pos.x += LIFE_SIZE;
    }
}

auto update_player_lives(int lives, int oam_start) -> void {
    for (auto i = 0; i < lives; ++i) {
        gba::display::oam_entry(oam_start + i).base_tile(3);
    }
    for (auto i = lives; i < MAX_LIVES; ++i) {
        gba::display::oam_entry(oam_start + i).base_tile(4);
    }
}

auto collides(Ball const& ball, gba::geometry::Rect const& hitbox) {
    auto [ball_x, ball_y] = ball.position;
    return (
        ball_x >= hitbox.x and ball_y >= hitbox.y and
        ball_x <= hitbox.x + hitbox.width and ball_y <= hitbox.y + hitbox.height
    );
}

struct MainScreen {
    bool game_running = false;

    Ball ball = {
        .oam_index = 2,
        .position =
            {SCREEN_SIZE.width / 2 - 1,
             (SCREEN_SIZE.height / 2) % SCREEN_SIZE.height},
        .speed = {-2, -2},
    };

    std::array<Player, 2> players = {
        Player{
            .oam_index = 0,
            .position = {0, 60},
            .speed = {0, 0},
            .lives = 3,
        },
        Player{
            .oam_index = 1,
            .position = {SCREEN_SIZE.width - PLAYER_WIDTH - 1, 60},
            .speed = {0, -2},
            .lives = 3
        },
    };

    auto start() -> void {
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

        ball = {
            .oam_index = 2,
            .position =
                {SCREEN_SIZE.width / 2 - 1,
                 (SCREEN_SIZE.height / 2 + seed) % SCREEN_SIZE.height},
            .speed = ball_dir,
        };

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
        if (ball.position.x <= 0 or ball.position.x >= SCREEN_SIZE.width - 3) {
            ball.speed.x *= -1;
        }

        if (ball.position.y <= 0 or ball.position.y >= SCREEN_SIZE.height - 3) {
            ball.speed.y *= -1;
        }
        ball.position.x += ball.speed.x;
        ball.position.y += ball.speed.y;

        if (ball.position.x >= SCREEN_SIZE.width - 3) {
            players[1].lives -= 1;
            update_player_lives(players[1].lives, 6);
            new_match(seed);
        } else if (ball.position.x == 0) {
            players[0].lives -= 1;
            update_player_lives(players[0].lives, 3);
            new_match(seed);
        }

        if (players[0].lives == 0 or players[1].lives == 0) {
            game_running = false;
        }

        // Update opponent position
        if (players[1].position.y == 0 or
            players[1].position.y >= 159 - PLAYER_HEIGHT) {
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
            ball.position.x = 15;
            ball.position.y = 15;
        }

        for (auto&& player : players) {
            player.move();
            if (player.position.y + PLAYER_HEIGHT > SCREEN_SIZE.height) {
                player.position.y = SCREEN_SIZE.height - PLAYER_HEIGHT;
            }
            if (player.position.y < 0) {
                player.position.y = 0;
            }
        }

        auto [p0, p1] = std::array{
            players[0].position,
            players[1].position,
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

        auto& entry = gba::display::oam_entry(ball.oam_index);
        entry.set_x(ball.position.x - 3);
        entry.set_y(ball.position.y - 3);
    }

    auto draw() const -> void {
        gba::display::vsync();
    }

    auto post_update() -> void {
    }
};

int main() {
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

    force_blank(true);

    change_mode(Mode::MODE0);
    layer_visible(Layer::BG1);
    layer_visible(Layer::OBJ);

    auto& ball_oam_entry = gba::display::oam_entry(2);
    ball_oam_entry.base_tile(2);
    auto& player0_oam = gba::display::oam_entry(0);
    player0_oam.base_tile(1);
    player0_oam.shape(gba::display::ObjectShape::VERTICAL);
    auto& player1_oam = gba::display::oam_entry(1);
    player1_oam.base_tile(1);
    player1_oam.shape(gba::display::ObjectShape::VERTICAL);
    gba::display::obj_palette()[1] = WHITE;
    gba::display::obj_palette()[2] = RED;
    gba::display::obj_palette()[3] = GREEN;

    gba::graphics::load_map(map);

    gba::display::sprite_tile(33) = gba::display::sprite_tile(1) =
        gba::display::map::Tile{{
            0x00001111,
            0x00001111,
            0x00001111,
            0x00001111,
            0x00001111,
            0x00001111,
            0x00001111,
            0x00001111,
        }};

    gba::display::sprite_tile(2) = gba::display::map::Tile{{
        0x00000000,
        0x00000000,
        0x00000000,
        0x00011000,
        0x00011000,
        0x00000000,
        0x00000000,
        0x00000000,
    }};

    gba::display::sprite_tile(3) = gba::display::map::Tile{{
        0x00000000,
        0x00000000,
        0x00000000,
        0x33333333,
        0x33333333,
        0x00000000,
        0x00000000,
        0x00000000,
    }};

    gba::display::sprite_tile(4) = gba::display::map::Tile{{
        0x20000002,
        0x02000020,
        0x00200200,
        0x00022000,
        0x00022000,
        0x00200200,
        0x02000020,
        0x20000002,
    }};

    auto screen = MainScreen{};

    force_blank(false);

    screen.start();
    while (true) {
        screen.update();
        screen.draw();
    }
}
