/**
 * \file demo_phone/virtual_devices/virtual_device_manager_device_register.c
 *
 * \brief Register a virtual device in the device manager.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "virtual_device.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Register a device in the virtual device manager.
 *
 * \param virt              The virtual device manager instance.
 * \param read              The read function for the virtual device.
 * \param write             The write function for the virtual device.
 * \param register_low      The lowest register number in the contiguous memory
 *                          mapped register space for this device.
 * \param register_high     The highest register number in the contiguous memory
 *                          mapped register space for this device.
 * \param context           The user context for the virtual device read/write
 *                          callbacks.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
virtual_device_manager_device_register(
    virtual_device_manager* virt, JEMU_SYM(j65c02_read_fn) read,
    JEMU_SYM(j65c02_write_fn) write, uint16_t register_low,
    uint16_t register_high, void* context)
{
    status retval;

    /* do we need to grow the device buffer? */
    if (virt->device_entries == virt->max_device_entries)
    {
        /* calculate the new max size. */
        size_t new_max_entries =
            virt->max_device_entries + (virt->max_device_entries / 2);

        /* attempt to reallocate the memory. */
        void* tmp =
            realloc(
                virt->devices, new_max_entries * sizeof(virtual_device_entry));
        if (NULL == tmp)
        {
            retval = JEMU_ERROR_OUT_OF_MEMORY;
            goto done;
        }

        /* update size and pointer. */
        virt->devices = (virtual_device_entry*)tmp;
        virt->max_device_entries = new_max_entries;
    }

    /* get the insert index and increment the number of device entries. */
    size_t idx = virt->device_entries;
    virt->device_entries += 1;

    /* set the values for this entry. */
    virt->devices[idx].register_low = register_low;
    virt->devices[idx].register_high = register_high;
    virt->devices[idx].context = context;
    virt->devices[idx].read = read;
    virt->devices[idx].write = write;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
