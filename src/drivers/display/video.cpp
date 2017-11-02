#include <drivers/display/video.h>
#include <drivers/utility.h>

namespace {

using gba::display::Page;
using gba::display::Color;
using gba::display::VRAMData;

static auto& vram_data = *new (reinterpret_cast<void*>(0x0600'0000)) std::array<VRAMData, 0x18000 / 2>{};
static auto& bg_palette = *new (reinterpret_cast<void*>(0x0500'0000)) std::array<Color, 256>{};

static auto page = Page::PAGE1;

}

std::array<VRAMData, 0x18000 / 2>& gba::display::vram_data() {
    return ::vram_data;
}

std::array<Color, 256>& gba::display::bg_palette() {
    return ::bg_palette;
}

Color& gba::display::mode5::vram(int x, int y) {
    return vram(x  + screen_width * y);
}

Color& gba::display::mode5::vram(int index) {
    return vram_data()[index + utils::value_of(::page) * screen_width * screen_height].color;
}

Page gba::display::mode5::page() {
    return ::page;
}

void gba::display::mode5::flip_pages() {
    select_page(::page);
    ::page = ::page == Page::PAGE0 ? Page::PAGE1 : Page::PAGE0;
}
