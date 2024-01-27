#ifndef LIBGBACPP_UTILS_BITSET_H
#define LIBGBACPP_UTILS_BITSET_H

#include <cstdint>

namespace gba::utils {

template<typename T>
class bitset_bit {
public:
    bitset_bit(T& value, std::size_t index)
        : index_(index)
        , value_(value)
    {}

    bitset_bit& operator=(bool bit) {
        if (bit) {
            value_ |= (1 << index_);
        } else {
            value_ &= ~(1 << index_);
        }
        return *this;
    };

    operator bool() const {
        return value_ & (1 << index_);
    }

    operator bool() {
        return value_ & (1 << index_);
    }

private:
    std::size_t index_;
    T& value_;
};

template<typename T>
class bitset {
public:
    bitset() = default;

    bitset(T value)
        : value_(value)
    {}

    auto operator[](std::size_t index) -> bitset_bit<T> {
        return bitset_bit(value_, index);
    }

    auto operator[](std::size_t index) const -> const bitset_bit<const T> {
        return bitset_bit(value_, index);
    }

    auto operator[](std::size_t index) volatile const -> const bitset_bit<const volatile T> {
        return bitset_bit(value_, index);
    }

    auto operator=(const T& other) -> uint32_t {
        value_ = other;
        return value_;
    }

    auto operator|=(const T& other) -> T& {
        value_ |= other;
        return value_;
    }

    auto to_ulong() const -> unsigned long int {
        return value_;
    }

private:
    T value_;
};

}

#endif
