/**
 * \file demo_phone/virtual_devices/virtual_device_via_create.c
 *
 * \brief Create the VIA virtual device.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jemu65c02/status.h>
#include <stdlib.h>
#include <string.h>

#include "via.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Create a virtual VIA device for the demo phone.
 *
 * \param via           Pointer to the virtual VIA device instance pointer to
 *                      be set to the created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
virtual_device_via_create(
    virtual_device_via** via)
{
    status retval;
    virtual_device_via* tmp = NULL;

    /* allocate memory for this device. */
    tmp = (virtual_device_via*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = JEMU_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* clear memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* initialize device. */
    /* NOP for now. */

    /* success. */
    *via = tmp;
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
