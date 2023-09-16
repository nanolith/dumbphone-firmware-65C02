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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
