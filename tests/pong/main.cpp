#include <random>

#include <libgba-cpp/arch/display/layers.h>
#include <libgba-cpp/arch/display/video.h>
#include <libgba-cpp/engine/input.h>
#include <libgba-cpp/utils/geometry.h>

using gba::geometry::Rect;

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

struct MovingObject {
    gba::geometry::Point position;
    gba::geometry::Point speed;

    auto move() -> void {
        this->position = {
            .x = this->position.x + speed.x,
            .y = this->position.y + speed.y,
        };
    }
};

struct Player {
    MovingObject object;
    int lives;
};

auto set_pixel(int x, int y, gba::display::Color const& color) -> void {
    gba::display::mode3::vram(x, y) = color.value();
}

auto draw_line_mid() -> void {
    for (auto y = 0; y < 160; ++y) {
        set_pixel(119, y, WHITE);
        set_pixel(120, y, WHITE);
    }
}

auto fill_rect(
    gba::geometry::Rect const& rect,
    gba::display::Color const& color
) -> void {
    for (auto x = rect.x; x < rect.x + rect.width; ++x) {
        for (auto y = rect.y; y < rect.y + rect.height; ++y) {
            set_pixel(x, y, color);
        }
    }
}

auto draw_square(
    gba::geometry::Point const& point,
    int size,
    gba::display::Color const& color
) -> void {
    fill_rect({point.x, point.y, size, size}, color);
}

auto draw_ball(int x, int y, gba::display::Color const& color) -> void {
    draw_square({x, y}, 2, color);
}

auto draw_player(
    gba::geometry::Point const& position,
    gba::display::Color const& color
) -> void {
    auto [x, y] = position;

    for (auto l = y; l < y + PLAYER_HEIGHT; ++l) {
        for (auto c = x; c < x + PLAYER_WIDTH; ++c) {
            set_pixel(c, l, color);
        }
    }
}

auto draw_lives(Player const& player, gba::geometry::Point point) -> void {
    for (auto i = 0; i < player.lives; ++i) {
        draw_square(point, LIFE_SIZE, WHITE);
        point.x += LIFE_SIZE;
    }
    for (auto i = player.lives; i < MAX_LIVES; ++i) {
        draw_square(point, LIFE_SIZE, RED);
        point.x += LIFE_SIZE;
    }
}

auto collides(MovingObject const& ball, gba::geometry::Rect const& hitbox) {
    auto [ball_x, ball_y] = ball.position;
    return (
        ball_x >= hitbox.x and ball_y >= hitbox.y and
        ball_x <= hitbox.x + hitbox.width and ball_y <= hitbox.y + hitbox.height
    );
}

struct MainScreen {
    using Point = gba::geometry::Point;

    bool game_running = false;

    MovingObject ball = {
        .position =
            {SCREEN_SIZE.width / 2 - 1,
             (SCREEN_SIZE.height / 2) % SCREEN_SIZE.height},
        .speed = Point{-2, -2},
    };

    std::array<Player, 2> players = {
        Player{
            .object = {
                .position = Point{0, 60},
                .speed = {0, 0},
            },
            .lives = 3
        },
        Player{
            .object = {
                .position = Point{SCREEN_SIZE.width - PLAYER_WIDTH - 1, 60},
                .speed = {0, -2},
            },
            .lives = 3
        },
    };

    auto new_match(int seed) -> void {
        auto ball_hor_dir = seed % 2 == 0 ? -1 : 1;
        auto ball_ver_dir = (seed / 3) % 2 == 0 ? -1 : 1;
        auto ball_h_speed = (seed / 17) % 2 + 1;
        auto ball_v_speed = (seed / 7) % 3 + 1;

        auto ball_dir =
            Point{ball_hor_dir * ball_h_speed, ball_ver_dir * ball_v_speed};

        this->ball = {
            .position =
                {SCREEN_SIZE.width / 2 - 1,
                 (SCREEN_SIZE.height / 2 + seed) % SCREEN_SIZE.height},
            .speed = ball_dir,
        };
    }
};

auto game_loop(MainScreen& screen, int seed) -> void {
    auto& [game_running, ball, players] = screen;

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
        screen.new_match(seed);
    } else if (ball.position.x == 0) {
        players[0].lives -= 1;
        screen.new_match(seed);
    }

    if (players[0].lives == 0 or players[1].lives == 0) {
        game_running = false;
    }

    // Update opponent position
    if (players[1].object.position.y == 0 or
        players[1].object.position.y >= 159 - PLAYER_HEIGHT) {
        players[1].object.speed.y *= -1;
    }

    using gba::input::Key;

    if (gba::input::pressing(Key::UP)) {
        players[0].object.speed.y = -2;
    } else if (gba::input::pressing(Key::DOWN)) {
        players[0].object.speed.y = 2;
    } else {
        players[0].object.speed.y = 0;
    }

    if (gba::input::pressing(Key::A)) {
        ball.position.x = 15;
        ball.position.y = 15;
    }

    for (auto&& player: players) {
        player.object.move();
        if (player.object.position.y + PLAYER_HEIGHT > SCREEN_SIZE.height) {
            player.object.position.y = SCREEN_SIZE.height - PLAYER_HEIGHT;
        }
        if (player.object.position.y < 0) {
            player.object.position.y = 0;
        }
    }

    auto [p0, p1] = std::array{players[0].object.position, players[1].object.position};

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
        ball.speed.y += players[0].object.speed.y;
    }

    if (collides_with_p1) {
        ball.speed.x *= -1;
        ball.speed.y += players[1].object.speed.y;
    }
}

int main() {
    auto gen = std::mt19937{std::random_device{}()};
    auto distrib = std::uniform_int_distribution<>{1, 1500};

    namespace display = gba::display;
    using gba::geometry::Point;
    display::force_blank(true);

    display::change_mode(display::Mode::MODE3);
    display::layer_visible(display::Layer::BG2);
    fill_rect({0, 0, SCREEN_SIZE.width, SCREEN_SIZE.height}, BLACK);

    display::force_blank(false);

    auto screen = MainScreen{};

    while (true) {
        // Game logic
        auto old_ball_position = screen.ball.position;
        auto old_player_position = screen.players[0].object.position;
        auto old_player2_position = screen.players[1].object.position;

        if (screen.game_running) {
            game_loop(screen, distrib(gen));
        } else {
            if (gba::input::pressing(gba::input::Key::START)) {
                screen.game_running = true;
                screen.players[0].lives = MAX_LIVES;
                screen.players[1].lives = MAX_LIVES;
                screen.new_match(distrib(gen));
            }
        }

        // Draw
        display::vsync();

        //   Clear objects
        draw_ball(old_ball_position.x, old_ball_position.y, BLACK);
        draw_player(old_player_position, BLACK);
        draw_player(old_player2_position, BLACK);

        //   Draw background
        draw_line_mid();

        //   Draw objects
        draw_ball(screen.ball.position.x, screen.ball.position.y, WHITE);
        draw_player(screen.players[0].object.position, WHITE);
        draw_player(screen.players[1].object.position, WHITE);

        draw_lives(
            screen.players[0],
            Point{SCREEN_SIZE.width / 2 - LIFE_SIZE * (MAX_LIVES + 1), 5}
        );
        draw_lives(
            screen.players[1],
            Point{SCREEN_SIZE.width / 2 + LIFE_SIZE, 5}
        );
    }
}
