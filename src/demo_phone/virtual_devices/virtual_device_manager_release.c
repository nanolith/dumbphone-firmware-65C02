/**
 * \file demo_phone/virtual_devices/virtual_device_manager_release.c
 *
 * \brief Release a virtual device manager instance.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "virtual_device.h"

/**
 * \brief Release a virtual device manager instance.
 *
 * \note After this call, the instance pointer is no longer valid.
 *
 * \param virt              The instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
virtual_device_manager_release(virtual_device_manager* virt)
{
    /* if devices is set, clear and free it. */
    if (NULL != virt->devices)
    {
        memset(
            virt->devices, 0,
            sizeof(*(virt->devices)) * virt->max_device_entries);
        free(virt->devices);
    }

    /* clear and free memory for this instance. */
    memset(virt, 0, sizeof(*virt));
    free(virt);

    return STATUS_SUCCESS;
}
