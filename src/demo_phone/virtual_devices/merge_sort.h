/**
 * \file demo_phone/virtual_devices/merge_sort.h
 *
 * \brief Simple inline merge sort utilities, split out to make them easier to
 * test.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <stdint.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Calculate the midpoint of two values.
 *
 * \param lower             The lower value for the midpoint.
 * \param upper             The upper value for the midpoint.
 *
 * \returns the midpoint between two values.
 */
inline size_t midpoint(size_t lower, size_t upper)
{
    size_t delta = upper - lower;

    delta /= 2;

    return lower + delta;
}

#define COMPARE_RESULT_LESSER                                               -1
#define COMPARE_RESULT_GREATER                                               1
#define COMPARE_RESULT_EQUAL                                                 0
#define COMPARE_RESULT_INTERSECTING                                      -1000

/**
 * \brief Compare two register ranges.
 *
 * \param x_low             The lower register address for the X range.
 * \param x_high            The higher register address for the X range.
 * \param y_low             The lower register address for the Y range.
 * \param y_high            The higher register address for the Y range.
 *
 * \returns a code indicating whether the ranges are equal, lesser, greater, or
 * intersecting.
 */
inline int register_range_compare(
    uint16_t x_low, uint16_t x_high, uint16_t y_low, uint16_t y_high)
{
    if (x_low < y_low && x_high < y_high && x_high < y_low)
    {
        return COMPARE_RESULT_LESSER;
    }
    else if (x_low > y_low && x_high > y_high && x_low > y_high)
    {
        return COMPARE_RESULT_GREATER;
    }
    else if (x_low == y_low && x_high == y_high)
    {
        return COMPARE_RESULT_EQUAL;
    }
    else
    {
        return COMPARE_RESULT_INTERSECTING;
    }
}

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
