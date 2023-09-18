/**
 * \file demo_phone/virtual_devices/status.h
 *
 * \brief Status codes for the virtual device manager.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <jemu65c02/status.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief There is an overlap in the device entries register ranges.
 */
#define VIRTUAL_DEVICE_ERROR_OVERLAP                                0x80001000

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
