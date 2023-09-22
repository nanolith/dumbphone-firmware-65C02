/**
 * \file demo_phone/virtual_devices/virtual_device_via_release.c
 *
 * \brief Release the VIA virtual device.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "via.h"

/**
 * \brief Release a virtual VIA device instance.
 *
 * \note After this call, the instance pointer is no longer valid.
 *
 * \param via           The instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
virtual_device_via_release(virtual_device_via* via)
{
    /* clear memory. */
    memset(via, 0, sizeof(*via));

    /* release memory. */
    free(via);

    /* success. */
    return STATUS_SUCCESS;
}
