/**
 * \file demo_phone/virtual_devices/virtual_device.h
 *
 * \brief Virtual device creation, registration, and termination.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <jemu65c02/function_decl.h>
#include <jemu65c02/status.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The virtual device instance.
 */
typedef struct virtual_device virtual_device;

/**
 * \brief Create a virtual device instance.
 *
 * \note On success, the caller is given ownership of the virtual device
 * instance and must release it by calling \ref virtual_device_release when it
 * is no longer needed.
 *
 * \param virt              Pointer to the virtual device instance pointer to
 *                          set to the created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
virtual_device_create(
    virtual_device** virt);

/**
 * \brief Release a virtual device instance.
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
virtual_device_release(virtual_device* virt);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
