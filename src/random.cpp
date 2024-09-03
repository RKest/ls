#include "ls/random.h"

using namespace ls;

Random::Random(uint32_t seed)
{
    g_lehmer64_state = seed;
}

auto Random::nextState() const -> uint64_t
{
    g_lehmer64_state *= 0xda942042e4dd58b5;
    return g_lehmer64_state >> 64;
}
