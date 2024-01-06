#ifndef GBA_UTILS_GENERAL_H
#define GBA_UTILS_GENERAL_H

#include <type_traits>
#include <random>

/**
 * General C++ Utilities.
 */
namespace utils {

/**
 * Extracts value from enum.
 */
template <typename Enum>
constexpr auto value_of(Enum e)
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

inline auto random() -> int {
    static auto gen = std::mt19937{std::random_device{}()};
    static auto distrib = std::uniform_int_distribution<>{1, 1500};

    return distrib(gen);
}


}

#endif
