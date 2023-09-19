/**
 * \file demo_phone/virtual_devices/virtual_device_manager_sort.c
 *
 * \brief Sort the virtual device entries in this virtual device manager
 * instance.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "merge_sort.h"
#include "status.h"
#include "virtual_device.h"

JEMU_IMPORT_jemu65c02;

/* forward decls. */
static status merge_sort(
    virtual_device_entry* array, virtual_device_entry* scratch, size_t entries);

/**
 * \brief The sort command must be called before emulation starts, as registered
 * devices are appended to the device array in an unsorted manner.
 *
 * \param virt              The virtual machine manager instance to sort.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) virtual_device_manager_sort(
    virtual_device_manager* virt)
{
    status retval;
    virtual_device_entry* scratch = NULL;

    /* allocate a scratch array for performing the sort. */
    scratch =
        (virtual_device_entry*)malloc(
            virt->device_entries * sizeof(virtual_device_entry));
    if (NULL == scratch)
    {
        retval = JEMU_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* perform the merge sort. */
    retval = merge_sort(virt->devices, scratch, virt->device_entries);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_scratch;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_scratch;

cleanup_scratch:
    memset(scratch, 0, virt->device_entries * sizeof(virtual_device_entry));
    free(scratch);

done:
    return retval;
}

/**
 * \brief Perform a merge sort on a subset of the virtual device entry array.
 *
 * \param array         The array to be sorted.
 * \param scratch       A scratch buffer to be used during sorting.
 *
 * This function performs a recursive merge sort on the array in-situ, using the
 * scratch array as a temporary buffer.
 */
static status merge_sort(
    virtual_device_entry* array, virtual_device_entry* scratch, size_t entries)
{
    status retval;

    /* if this array is trivially sorted, then just return. */
    if (entries <= 1)
    {
        return STATUS_SUCCESS;
    }

    /* compute the left-hand and right-hand array sizes. */
    size_t lhs_size = entries / 2;
    size_t rhs_size = entries - lhs_size;

    /* compute the left and right arrays. */
    virtual_device_entry* left_array = array;
    virtual_device_entry* right_array = array + lhs_size;

    /* recursively sort the left-hand side array. */
    retval = merge_sort(left_array, scratch, lhs_size);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* recursively sort the right-hand side array. */
    retval = merge_sort(right_array, scratch + lhs_size, rhs_size);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* merge the two sorted arrays into the scratch array. */
    size_t lhs_idx = 0, rhs_idx = 0, out_idx = 0;
    while (lhs_idx < lhs_size && rhs_idx < rhs_size)
    {
        virtual_device_entry* lhs_ent = left_array + lhs_idx;
        virtual_device_entry* rhs_ent = right_array + rhs_idx;

        /* compare the two entries. */
        int cmp =
            register_range_compare(
                lhs_ent->register_low, lhs_ent->register_high,
                rhs_ent->register_low, rhs_ent->register_high);
        if (COMPARE_RESULT_LESSER == cmp)
        {
            memcpy(scratch + out_idx, lhs_ent, sizeof(*lhs_ent));
            ++lhs_idx;
        }
        else if (COMPARE_RESULT_GREATER == cmp)
        {
            memcpy(scratch + out_idx, rhs_ent, sizeof(*rhs_ent));
            ++rhs_idx;
        }
        else
        {
            /* the two register ranges overlap. */
            return VIRTUAL_DEVICE_ERROR_OVERLAP;
        }

        /* increment the output index. */
        ++out_idx;
    }

    /* copy any remaining entries from the left array. */
    if (lhs_idx < lhs_size)
    {
        size_t remaining = lhs_size - lhs_idx;
        memcpy(
            scratch + out_idx, left_array + lhs_idx,
            remaining * sizeof(virtual_device_entry));
        out_idx += remaining;
    }

    /* copy any remaining entries from the right array. */
    if (rhs_idx < rhs_size)
    {
        size_t remaining = rhs_size - rhs_idx;
        memcpy(
            scratch + out_idx, right_array + rhs_idx,
            remaining * sizeof(virtual_device_entry));
        out_idx += remaining;
    }

    /* copy the sorted scratch array over top of the array. */
    memcpy(array, scratch, entries * sizeof(virtual_device_entry));

    /* success. */
    return STATUS_SUCCESS;
}
