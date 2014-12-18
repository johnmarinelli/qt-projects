#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

/*
 * given actual T1, finds nearest multiple of T2.
 * usually used for snap-to-grid.
 */
template <typename T1, typename T2>
T1 getNearestMultiple(const T1& actual, const T2& multiple)
{
    return std::ceil(actual / multiple) * multiple;
}

/*
 * bool to string
 */
inline const char* const boolToString(const bool b)
{
    return b ? "True" : "False";
}

#endif // UTILITY_H
