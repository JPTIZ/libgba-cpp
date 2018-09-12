#include <libgba-cpp/engine/game.h>
#include "scenes.h"


using namespace gba::engine;


int main() {
    auto game = Game();
    game.set_scene(new scene::Title{game});

    while (true) {
        auto scene = game.scene();
        if (scene) {
            scene->run();
        }
    }
}
