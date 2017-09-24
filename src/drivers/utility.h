#ifndef GBA_UTILITY_H
#define GBA_UTILITY_H

#include <type_traits>

namespace utils {

template <typename Enum>
constexpr auto value_of(Enum e)
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

}

#endif
