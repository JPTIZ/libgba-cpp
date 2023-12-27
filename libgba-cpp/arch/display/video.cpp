#include <libgba-cpp/arch/display/video.h>
#include <libgba-cpp/utils/general.h>

namespace {

using gba::display::Page;
using gba::display::Color;
using gba::display::RawPalette;

static auto page = Page::PAGE1;

}

Color& gba::display::mode5::vram(int x, int y) {
    return vram(x  + screen_width * y);
}

Color& gba::display::mode5::vram(int index) {
    return vram_data<gba::display::mode5::VRAMData>()[index + utils::value_of(::page) * screen_width * screen_height];
}

Page gba::display::mode5::page() {
    return ::page;
}

void gba::display::mode5::flip_pages() {
    select_page(::page);

    constexpr auto PAGE0 = Page::PAGE0;
    constexpr auto PAGE1 = Page::PAGE1;
    ::page = ::page == PAGE0 ? PAGE1 : PAGE0;
}
