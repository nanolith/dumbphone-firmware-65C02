/**
 * \file demo_phone/virtual_devices/virtual_device.h
 *
 * \brief Virtual device creation, registration, and termination.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <jemu65c02/jemu65c02.h>
#include <stddef.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief A virtual device entry.
 */
typedef struct virtual_device_entry virtual_device_entry;

struct virtual_device_entry
{
    uint16_t register_low;
    uint16_t register_high;
    void* context;
    JEMU_SYM(j65c02_read_fn) read;
    JEMU_SYM(j65c02_write_fn) write;
};

/**
 * \brief The virtual device manager instance.
 */
typedef struct virtual_device_manager virtual_device_manager;

struct virtual_device_manager
{
    virtual_device_entry* devices;
    size_t device_entries;
    size_t max_device_entries;
};

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
    virtual_device_manager** virt);

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
virtual_device_manager_release(virtual_device_manager* virt);

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
    uint16_t register_high, void* context);

/**
 * \brief Return true if the given address is covered by the virtual device map.
 *
 * \param virt              The virtual device manager instance.
 * \param address           The memory address.
 *
 * \returns true if the given memory address is covered by the virtual device
 * map.
 */
bool virtual_device_manager_address_mapped(
    const virtual_device_manager* virt);

/**
 * \brief Given an opaque reference to a device manager, perform the JEMU65C02
 * read function for the device manager.
 *
 * \param virt              An opaque reference to the device manager instance.
 * \param addr              The address for the read operation.
 * \param byte              Pointer to receive the byte read.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) virtual_device_manager_emu_read_callback(
    void* virt, uint16_t addr, uint8_t* byte);

/**
 * \brief Given an opaque reference to a device manager, perform the JEMU65C02
 * write function for the device manager.
 *
 * \param virt              An opaque reference to the device manager instance.
 * \param addr              The address for the write operation.
 * \param byte              The byte to write.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) virtual_device_manager_emu_write_callback(
    void* virt, uint16_t addr, uint8_t byte);

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
    virtual_device_manager* virt);

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
    virtual_device_manager* virt, uint16_t reg);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
