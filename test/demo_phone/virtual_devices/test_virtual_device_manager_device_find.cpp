#include <minunit/minunit.h>

#include "../../../src/demo_phone/virtual_devices/status.h"
#include "../../../src/demo_phone/virtual_devices/virtual_device.h"

JEMU_IMPORT_jemu65c02;

TEST_SUITE(virtual_device_manager_device_find);

/**
 * \brief Find fails when there are no entries to find.
 */
TEST(fail_empty)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x1234;

    /* create the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_create(&virt));

    /* find will fail because there are no device entries to search. */
    TEST_ASSERT(NULL == virtual_device_manager_device_find(virt, REG));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Find fails when the register is less than the added register range.
 */
TEST(fail_single_less)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0050;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* create the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_create(&virt));

    /* add an entry to the device manager. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVA_READ, DEVA_WRITE, DEVA_REGISTER_LOW,
                    DEVA_REGISTER_HIGH, DEVA_CONTEXT));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* find will fail because the register is less than the device entry. */
    TEST_ASSERT(NULL == virtual_device_manager_device_find(virt, REG));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Find fails when the register is greater than the added register range.
 */
TEST(fail_single_greater)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x5000;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* create the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_create(&virt));

    /* add an entry to the device manager. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVA_READ, DEVA_WRITE, DEVA_REGISTER_LOW,
                    DEVA_REGISTER_HIGH, DEVA_CONTEXT));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* find will fail because the register is greater than the device entry. */
    TEST_ASSERT(NULL == virtual_device_manager_device_find(virt, REG));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Find succeeds when the register falls in the device register range.
 */
TEST(success_single_equal)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0110;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* create the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_create(&virt));

    /* add an entry to the device manager. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == virtual_device_manager_device_register(
                    virt, DEVA_READ, DEVA_WRITE, DEVA_REGISTER_LOW,
                    DEVA_REGISTER_HIGH, DEVA_CONTEXT));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* find will succeed. */
    TEST_ASSERT(virt->devices == virtual_device_manager_device_find(virt, REG));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search fails if it is below the range of the lowest device.
 */
TEST(fail_multi_less)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0050;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will fail because the register is less than the device entries. */
    TEST_ASSERT(NULL == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search fails if it is above the range of the highest device.
 */
TEST(fail_multi_greater)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0600;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will fail because the reg is greater than the device entries. */
    TEST_ASSERT(NULL == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search succeeds if it is within the range of the first device.
 */
TEST(success_multi_first)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0101;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will succeed. */
    TEST_ASSERT(virt->devices == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search fails if it is between the first and second devices.
 */
TEST(fail_multi_first_second)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0200;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will fail because the reg is between the first and second devs. */
    TEST_ASSERT(NULL == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search succeeds if it is within the range of the second device.
 */
TEST(success_multi_second)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0201;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will succeed. */
    TEST_ASSERT(
        virt->devices + 1 == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search fails if it is between the second and third devices.
 */
TEST(fail_multi_second_third)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0300;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will fail because the reg is between the second and third devs. */
    TEST_ASSERT(NULL == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search succeeds if it is within the range of the third device.
 */
TEST(success_multi_third)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0301;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will succeed. */
    TEST_ASSERT(
        virt->devices + 2 == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search fails if it is between the third and fourth devices.
 */
TEST(fail_multi_third_fourth)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0400;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will fail because the reg is between the third and fourth devs. */
    TEST_ASSERT(NULL == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search succeeds if it is within the range of the fourth device.
 */
TEST(success_multi_fourth)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0401;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will succeed. */
    TEST_ASSERT(
        virt->devices + 3 == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search fails if it is between the fourth and fifth devices.
 */
TEST(fail_multi_fourth_fifth)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0500;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will fail because the reg is between the fourth and fifth devs. */
    TEST_ASSERT(NULL == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}

/**
 * \brief Search succeeds if it is within the range of the fifth device.
 */
TEST(success_multi_fifth)
{
    virtual_device_manager* virt;
    const uint16_t REG = 0x0501;

    /* device entry A. */
    uint16_t DEVA_REGISTER_LOW = 0x0101;
    uint16_t DEVA_REGISTER_HIGH = 0x01FF;
    void* DEVA_CONTEXT = (void*)0x1000;
    j65c02_read_fn DEVA_READ = (j65c02_read_fn)0x1001;
    j65c02_write_fn DEVA_WRITE = (j65c02_write_fn)0x1002;

    /* device entry B. */
    uint16_t DEVB_REGISTER_LOW = 0x0201;
    uint16_t DEVB_REGISTER_HIGH = 0x02FF;
    void* DEVB_CONTEXT = (void*)0x2000;
    j65c02_read_fn DEVB_READ = (j65c02_read_fn)0x2001;
    j65c02_write_fn DEVB_WRITE = (j65c02_write_fn)0x2002;

    /* device entry C. */
    uint16_t DEVC_REGISTER_LOW = 0x0301;
    uint16_t DEVC_REGISTER_HIGH = 0x03FF;
    void* DEVC_CONTEXT = (void*)0x3000;
    j65c02_read_fn DEVC_READ = (j65c02_read_fn)0x3001;
    j65c02_write_fn DEVC_WRITE = (j65c02_write_fn)0x3002;

    /* device entry D. */
    uint16_t DEVD_REGISTER_LOW = 0x0401;
    uint16_t DEVD_REGISTER_HIGH = 0x04FF;
    void* DEVD_CONTEXT = (void*)0x4000;
    j65c02_read_fn DEVD_READ = (j65c02_read_fn)0x4001;
    j65c02_write_fn DEVD_WRITE = (j65c02_write_fn)0x4002;

    /* device entry E. */
    uint16_t DEVE_REGISTER_LOW = 0x0501;
    uint16_t DEVE_REGISTER_HIGH = 0x05FF;
    void* DEVE_CONTEXT = (void*)0x5000;
    j65c02_read_fn DEVE_READ = (j65c02_read_fn)0x5001;
    j65c02_write_fn DEVE_WRITE = (j65c02_write_fn)0x5002;

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

    /* find will succeed. */
    TEST_ASSERT(
        virt->devices + 4 == virtual_device_manager_device_find(virt, REG));

    /* Sort the entries. */
    TEST_ASSERT(
        STATUS_SUCCESS == virtual_device_manager_sort(virt));

    /* release the manager. */
    TEST_ASSERT(STATUS_SUCCESS == virtual_device_manager_release(virt));
}
