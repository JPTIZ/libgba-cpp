#ifndef GBA_UTILITY_H
#define GBA_UTILITY_H

#include <iterator>
#include <utility>
#include <type_traits>

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

template <typename Iterable>
class Enumeration {
public:
    struct Iterator {
        std::size_t i = 0u;
        typename Iterable::const_iterator it;

        const auto operator*() const noexcept {
            return std::pair{i, *it};
        }

        auto operator++() noexcept {
            return Iterator{++i, ++it};
        }
    };

    Enumeration(const Iterable& iterable):
        iterable{iterable}
    {}

    auto begin() const noexcept {
        return Iterator{0u, std::begin(iterable)};
    }

    auto end() const noexcept {
        auto [begin, end] = std::pair{std::begin(iterable),
                                      std::end(iterable)};
        return Iterator{std::size_t(std::distance(begin, end)), end};
    }

    const Iterable& iterable;
};

template <typename T>
auto operator!=(const T& lhs, const T& rhs) {
    return *lhs != *rhs;
}

template <typename T>
auto enumerate(const T& iterable) {
    return Enumeration<T>{iterable};
}

}

#endif
