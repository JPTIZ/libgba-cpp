#include "effects.h"

namespace gba::display {

/**
 * Data for mosaic effect.
 */
class MosaicRegister {
public:
    MosaicRegister() = default;

    void bg_h(unsigned amount) {
        data = (data & ~(0b1111u << 0)) | ((amount & 0b1111) << 0);
        mosaic_register = data;
    }

    void bg_v(unsigned amount) {
        data = (data & ~(0b1111u << 4)) | ((amount & 0b1111) << 4);
        mosaic_register = data;
    }

    void obj_h(unsigned amount) {
        data = (data & ~(0b1111u << 8)) | ((amount & 0b1111) << 8);
        mosaic_register = data;
    }

    void obj_v(unsigned amount) {
        data = (data & ~(0b1111u << 0xc)) | ((amount & 0b1111) << 0xc);
        mosaic_register = data;
    }

private:
    uint16_t data = 0;
    uint16_t& mosaic_register = *reinterpret_cast<uint16_t*>(0x0400'004c);
};

}
