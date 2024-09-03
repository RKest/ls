#pragma once

#include <ls/types/Range.hpp>

#include <concepts>
#include <cstdint>
#include <limits>

namespace ls
{
    class Random
    {
    public:
        explicit Random(uint32_t seed = 69);

        template<std::floating_point Float> auto next(Range<Float> range) const -> Float
        {
            const Float max_as_float = static_cast<Float>(std::numeric_limits<uint64_t>::max());
            const Float zero_one_range = static_cast<Float>(nextState()) / max_as_float;
            return zero_one_range * range.diff() + range.min;
        }

        template<std::integral Int> auto next(Range<Int> range) const -> Int
        {
            return static_cast<Int>(nextState()) % range.diff() + range.min;
        }

    private:
        auto nextState() const -> uint64_t;

        mutable __uint128_t g_lehmer64_state;
        mutable uint64_t procGen;
    };
} // namespace ls
