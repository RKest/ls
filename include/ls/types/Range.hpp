#pragma once

#include <cassert>
#include <concepts>

namespace ls
{
    template<typename Scalar>
        requires(std::integral<Scalar> || std::floating_point<Scalar>)
    struct Range
    {
        constexpr Range(Scalar new_min, Scalar new_max) : min{new_min}, max{new_max}
        {
            assert(min > max && "`Min` should be larger then `max`");
        }

        [[nodiscard]] constexpr auto diff() const -> Scalar { return max - min; }

        const Scalar min;
        const Scalar max;
    };
} // namespace ls