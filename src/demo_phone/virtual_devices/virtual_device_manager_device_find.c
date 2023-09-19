/**
 * \file demo_phone/virtual_devices/virtual_device_manager_device_find.c
 *
 * \brief Find a device entry that services the given memory mapped register.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stddef.h>

#include "merge_sort.h"
#include "virtual_device.h"

/* forward decls. */
static virtual_device_entry* binary_search(
    virtual_device_entry* array, size_t entries, uint16_t reg);

/**
 * \brief Given a sorted virtual device manager and a register location, find a
 * device entry or NULL if no device entry was found.
 *
 * \param virt              The virtual device manager instance.
 * \param reg               The register location.
 *
 * \returns the virtual device entry for this register location or NULL.
 */
virtual_device_entry* virtual_device_manager_device_find(
    virtual_device_manager* virt, uint16_t reg)
{
    return binary_search(virt->devices, virt->device_entries, reg);
}

/**
 * \brief Perform a recursive binary search for the given register value.
 *
 * \param array             The sorted array to search.
 * \param entries           The number of entries in this array.
 * \param reg               The register to search.
 *
 * \returns the virtual device entry that services this register or NULL if not
 * found.
 */
static virtual_device_entry* binary_search(
    virtual_device_entry* array, size_t entries, uint16_t reg)
{
    /* if there are no entries, there is no result to be found. */
    if (0 == entries)
    {
        return NULL;
    }
    /* if there is only one entry, then check that entry. */
    else if (1 == entries)
    {
        if (array[0].register_low <= reg && array[0].register_high >= reg)
        {
            return array + 0;
        }
        else
        {
            return NULL;
        }
    }
    /* recursive case. */
    else
    {
        /* compute the midpoint of this array. */
        size_t mid = midpoint(0, entries);

        /* should we search the lower range? */
        if (reg < array[mid].register_low && mid > 0)
        {
            return binary_search(array, mid, reg);
        }
        /* should we search the upper range? */
        else if (reg > array[mid].register_high && mid < entries)
        {
            return binary_search(array + mid, entries - mid, reg);
        }
        /* does this entry match? */
        else if (
            array[mid].register_low <= reg && array[mid].register_high >= reg)
        {
            return array + mid;
        }
        /* there are no more results to find. */
        else
        {
            return NULL;
        }
    }
}
