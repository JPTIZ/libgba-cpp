#ifndef LIBGBA_CPP_ENGINE_SCENE_H
#define LIBGBA_CPP_ENGINE_SCENE_H


#include <memory>


namespace gba::engine {

class Scene {
public:
    virtual ~Scene() = 0;

    virtual void run() = 0;
};

}


#endif
