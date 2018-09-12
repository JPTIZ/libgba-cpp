#ifndef LIBGBA_ENGINE_GAME_H
#define LIBGBA_ENGINE_GAME_H

#include <libgba-cpp/engine/scene.h>

namespace gba::engine {

class Game {
public:
    Game() = default;

    void set_scene(Scene* s) {
        delete scene_;
        scene_ = s;
    }

    auto scene() const {
        return scene_;
    }
public:
    Scene* scene_ = nullptr;
};

}


#endif
