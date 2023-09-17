/**
 * \file demo_phone/virtual_devices/virtual_device_manager_create.c
 *
 * \brief Create a virtual device manager instance.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "virtual_device.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Create a virtual device manager instance.
 *
 * \note On success, the caller is given ownership of the virtual device
 * instance and must release it by calling \ref virtual_device_release when it
 * is no longer needed.
 *
 * \param virt              Pointer to the virtual device manager instance
 *                          pointer to set to the created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
virtual_device_manager_create(
    virtual_device_manager** virt)
{
    status retval;
    virtual_device_manager* tmp = NULL;

    /* allocate memory for the instance. */
    tmp = (virtual_device_manager*)malloc(sizeof(*tmp));
    if (NULL != tmp)
    {
        retval = JEMU_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* initialize instance. */
    tmp->device_entries = 0;
    tmp->max_device_entries = 10;

    /* allocate memory for the device array. */
    tmp->devices = (virtual_device_entry*)malloc(sizeof(*(tmp->devices)) * 10);
    if (NULL == tmp->devices)
    {
        retval = JEMU_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* clear the device array. */
    memset(tmp->devices, 0, sizeof(*(tmp->devices)) * 10);

    /* success. */
    retval = STATUS_SUCCESS;
    *virt = tmp;
    goto done;

cleanup_tmp:
    memset(tmp, 0, sizeof(*tmp));
    free(tmp);

done:
    return retval;
}
