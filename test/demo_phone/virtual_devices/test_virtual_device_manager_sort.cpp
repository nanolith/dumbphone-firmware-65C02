#include <minunit/minunit.h>

#include "../../../src/demo_phone/virtual_devices/status.h"
#include "../../../src/demo_phone/virtual_devices/virtual_device.h"

JEMU_IMPORT_jemu65c02;

TEST_SUITE(virtual_device_manager_sort);

/**
 * \brief Sort fails when the exact device is added twice.
 */
TEST(fail_equal)
{
    virtual_device_manager* virt;

    /* create the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_create(&virt));

    /* Create two dummy entries that are exactly the same. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, NULL, NULL, 1, 5, NULL));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, NULL, NULL, 1, 5, NULL));

    /* Sort should fail. */
    TEST_EXPECT(
        VIRTUAL_DEVICE_ERROR_OVERLAP == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Sort fails when two devices have intersecting register ranges.
 */
TEST(fail_intersect)
{
    virtual_device_manager* virt;

    /* create the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_create(&virt));

    /* Create two dummy entries that are exactly the same. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, NULL, NULL, 1, 3, NULL));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, NULL, NULL, 2, 5, NULL));

    /* Sort should fail. */
    TEST_EXPECT(
        VIRTUAL_DEVICE_ERROR_OVERLAP == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief We can sort five in order items.
 */
TEST(succeed_in_order_sort)
{
    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0100;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0200;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0300;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0400;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0500;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

    virtual_device_manager* virt;

    /* create the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_create(&virt));

    /* Create five entries. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVA_READ, DEVA_WRITE, DEVA_REGISTER_LOW,
                    DEVA_REGISTER_HIGH, DEVA_CONTEXT));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVB_READ, DEVB_WRITE, DEVB_REGISTER_LOW,
                    DEVB_REGISTER_HIGH, DEVB_CONTEXT));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVC_READ, DEVC_WRITE, DEVC_REGISTER_LOW,
                    DEVC_REGISTER_HIGH, DEVC_CONTEXT));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVD_READ, DEVD_WRITE, DEVD_REGISTER_LOW,
                    DEVD_REGISTER_HIGH, DEVD_CONTEXT));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVE_READ, DEVE_WRITE, DEVE_REGISTER_LOW,
                    DEVE_REGISTER_HIGH, DEVE_CONTEXT));

    /* Sort should succeed. */
    TEST_EXPECT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* the first entry should be DEVA. */
    TEST_EXPECT(DEVA_REGISTER_LOW == virt->devices[0].register_low);
    TEST_EXPECT(DEVA_REGISTER_HIGH == virt->devices[0].register_high);
    TEST_EXPECT(DEVA_CONTEXT == virt->devices[0].context);
    TEST_EXPECT(DEVA_READ == virt->devices[0].read);
    TEST_EXPECT(DEVA_WRITE == virt->devices[0].write);

    /* the second entry should be DEVB. */
    TEST_EXPECT(DEVB_REGISTER_LOW == virt->devices[1].register_low);
    TEST_EXPECT(DEVB_REGISTER_HIGH == virt->devices[1].register_high);
    TEST_EXPECT(DEVB_CONTEXT == virt->devices[1].context);
    TEST_EXPECT(DEVB_READ == virt->devices[1].read);
    TEST_EXPECT(DEVB_WRITE == virt->devices[1].write);

    /* the third entry should be DEVC. */
    TEST_EXPECT(DEVC_REGISTER_LOW == virt->devices[2].register_low);
    TEST_EXPECT(DEVC_REGISTER_HIGH == virt->devices[2].register_high);
    TEST_EXPECT(DEVC_CONTEXT == virt->devices[2].context);
    TEST_EXPECT(DEVC_READ == virt->devices[2].read);
    TEST_EXPECT(DEVC_WRITE == virt->devices[2].write);

    /* the fourth entry should be DEVD. */
    TEST_EXPECT(DEVD_REGISTER_LOW == virt->devices[3].register_low);
    TEST_EXPECT(DEVD_REGISTER_HIGH == virt->devices[3].register_high);
    TEST_EXPECT(DEVD_CONTEXT == virt->devices[3].context);
    TEST_EXPECT(DEVD_READ == virt->devices[3].read);
    TEST_EXPECT(DEVD_WRITE == virt->devices[3].write);

    /* the fifth entry should be DEVE. */
    TEST_EXPECT(DEVE_REGISTER_LOW == virt->devices[4].register_low);
    TEST_EXPECT(DEVE_REGISTER_HIGH == virt->devices[4].register_high);
    TEST_EXPECT(DEVE_CONTEXT == virt->devices[4].context);
    TEST_EXPECT(DEVE_READ == virt->devices[4].read);
    TEST_EXPECT(DEVE_WRITE == virt->devices[4].write);

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief We can sort five reversed devices.
 */
TEST(succeed_reverse_sort)
{
    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0100;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0200;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0300;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0400;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0500;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

    virtual_device_manager* virt;

    /* create the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_create(&virt));

    /* Create five entries. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVE_READ, DEVE_WRITE, DEVE_REGISTER_LOW,
                    DEVE_REGISTER_HIGH, DEVE_CONTEXT));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVD_READ, DEVD_WRITE, DEVD_REGISTER_LOW,
                    DEVD_REGISTER_HIGH, DEVD_CONTEXT));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVC_READ, DEVC_WRITE, DEVC_REGISTER_LOW,
                    DEVC_REGISTER_HIGH, DEVC_CONTEXT));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVB_READ, DEVB_WRITE, DEVB_REGISTER_LOW,
                    DEVB_REGISTER_HIGH, DEVB_CONTEXT));
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVA_READ, DEVA_WRITE, DEVA_REGISTER_LOW,
                    DEVA_REGISTER_HIGH, DEVA_CONTEXT));

    /* Sort should succeed. */
    TEST_EXPECT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* the first entry should be DEVA. */
    TEST_EXPECT(DEVA_REGISTER_LOW == virt->devices[0].register_low);
    TEST_EXPECT(DEVA_REGISTER_HIGH == virt->devices[0].register_high);
    TEST_EXPECT(DEVA_CONTEXT == virt->devices[0].context);
    TEST_EXPECT(DEVA_READ == virt->devices[0].read);
    TEST_EXPECT(DEVA_WRITE == virt->devices[0].write);

    /* the second entry should be DEVB. */
    TEST_EXPECT(DEVB_REGISTER_LOW == virt->devices[1].register_low);
    TEST_EXPECT(DEVB_REGISTER_HIGH == virt->devices[1].register_high);
    TEST_EXPECT(DEVB_CONTEXT == virt->devices[1].context);
    TEST_EXPECT(DEVB_READ == virt->devices[1].read);
    TEST_EXPECT(DEVB_WRITE == virt->devices[1].write);

    /* the third entry should be DEVC. */
    TEST_EXPECT(DEVC_REGISTER_LOW == virt->devices[2].register_low);
    TEST_EXPECT(DEVC_REGISTER_HIGH == virt->devices[2].register_high);
    TEST_EXPECT(DEVC_CONTEXT == virt->devices[2].context);
    TEST_EXPECT(DEVC_READ == virt->devices[2].read);
    TEST_EXPECT(DEVC_WRITE == virt->devices[2].write);

    /* the fourth entry should be DEVD. */
    TEST_EXPECT(DEVD_REGISTER_LOW == virt->devices[3].register_low);
    TEST_EXPECT(DEVD_REGISTER_HIGH == virt->devices[3].register_high);
    TEST_EXPECT(DEVD_CONTEXT == virt->devices[3].context);
    TEST_EXPECT(DEVD_READ == virt->devices[3].read);
    TEST_EXPECT(DEVD_WRITE == virt->devices[3].write);

    /* the fifth entry should be DEVE. */
    TEST_EXPECT(DEVE_REGISTER_LOW == virt->devices[4].register_low);
    TEST_EXPECT(DEVE_REGISTER_HIGH == virt->devices[4].register_high);
    TEST_EXPECT(DEVE_CONTEXT == virt->devices[4].context);
    TEST_EXPECT(DEVE_READ == virt->devices[4].read);
    TEST_EXPECT(DEVE_WRITE == virt->devices[4].write);

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}
