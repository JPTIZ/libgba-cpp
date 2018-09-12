#ifndef EXAMPLES_SHOOTER_SCENES_H
#define EXAMPLES_SHOOTER_SCENES_H


#include <libgba-cpp/engine/game.h>
#include <libgba-cpp/engine/scene.h>
#include <libgba-cpp/engine/graphics.h>


namespace scene {

class Title: public gba::engine::Scene {
    using Game = gba::engine::Game;
    using Sprite = gba::graphics::Sprite;
public:
    Title(Game& game);
    ~Title();

    void run() override;

private:
    Game& game;
    Sprite cursor;
};

}

#endif
