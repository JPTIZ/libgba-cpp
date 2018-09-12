#include "../scenes.h"

#include <libgba-cpp/engine/graphics.h>

using namespace gba::engine;

namespace scene {

Title::Title(Game& game):
    game{game},
    cursor{Sprite{shooter::sprites::cursor}}
{}

void Title::run() {
    change_mode(Mode::MODE3);
    mode3::set_background(shooter::title_bg);

    while (game.scene() == this) {
        update();
    }
}

void Title::update() {
    input::update();

    if (input::pressing(input::Key::UP)) {
        --index;
    } else if (input::pressing(input::Key::DOWN)) {
        ++index;
    } else if (input::pressing(input::Key::A)) {
        on_select(index);
    }

    if (index < 0) {
        index = 2;
    } else if (index > 2) {
        index = 0;
    }

    cursor.y = 80 + index * 32;
}

void Title::on_select(int index) {
    switch (index) {
    case 0:
        game.set_scene(scene::Map{shooter::maps::map001});
        break;
    case 1:
        game.set_scene(scene::Load{});
        break;
    case 2:
        game.set_scene(scene::Options{});
        break;
    }
}

}
