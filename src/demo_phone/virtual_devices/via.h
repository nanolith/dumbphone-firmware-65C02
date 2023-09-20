/**
 * \file demo_phone/virtual_devices/via.h
 *
 * \brief Virtual VIA device for the demo phone.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include "virtual_device.h"

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

#define VIA_REGISTER_IORB           0xF600
#define VIA_REGISTER_IORA           0xF601
#define VIA_REGISTER_DDRB           0xF602
#define VIA_REGISTER_DDRA           0xF603
#define VIA_REGISTER_T1C1L          0xF604
#define VIA_REGISTER_T1C1H          0xF605
#define VIA_REGISTER_T1LL           0xF606
#define VIA_REGISTER_T1LH           0xF607
#define VIA_REGISTER_T2CL           0xF608
#define VIA_REGISTER_T2CH           0xF609
#define VIA_REGISTER_SR             0xF60A
#define VIA_REGISTER_ACR            0xF60B
#define VIA_REGISTER_PCR            0xF60C
#define VIA_REGISTER_IFR            0xF60D
#define VIA_REGISTER_IER            0xF60E
#define VIA_REGISTER_IORA           0xF60F

/**
 * \brief The VIA virtual device.
 */
typedef struct virtual_device_via virtual_device_via;

struct virtual_device_via
{
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
