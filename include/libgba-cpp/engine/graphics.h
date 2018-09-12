#ifndef LIBGBA_CPP_ENGINE_GRAPHICS_H
#define LIBGBA_CPP_ENGINE_GRAPHICS_H

#include <libgba-cpp/arch/display/video.h>

namespace gba::graphics {

using Mode = gba::display::Mode;

inline void change_mode(Mode mode) {
    gba::display::change_mode(mode);
}

}

#endif
