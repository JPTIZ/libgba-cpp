#ifndef LIBGBA_CPP_ENGINE_INPUT_H
#define LIBGBA_CPP_ENGINE_INPUT_H

namespace gba::input {

enum class Key {
    A,
    B,
    SELECT,
    START,
    RIGHT,
    LEFT,
    UP,
    DOWN,
    R,
    L,
};

bool pressing(Key);
void update();

}

#endif
