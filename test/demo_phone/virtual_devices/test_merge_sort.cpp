#include <minunit/minunit.h>

#include "../../../src/demo_phone/virtual_devices/merge_sort.h"

TEST_SUITE(merge_sort);

/**
 * \brief Test the midpoint function.
 */
TEST(midpoint)
{
    TEST_EXPECT(0 == midpoint(0, 0));
    TEST_EXPECT(0 == midpoint(0, 1));
    TEST_EXPECT(1 == midpoint(0, 2));
    TEST_EXPECT(1 == midpoint(0, 3));
    TEST_EXPECT(2 == midpoint(0, 4));
    TEST_EXPECT(1 == midpoint(1, 1));
    TEST_EXPECT(1 == midpoint(1, 2));
    TEST_EXPECT(2 == midpoint(1, 3));
    TEST_EXPECT(2 == midpoint(1, 4));
    TEST_EXPECT(3 == midpoint(1, 5));
    TEST_EXPECT(2 == midpoint(2, 2));
    TEST_EXPECT(2 == midpoint(2, 3));
    TEST_EXPECT(3 == midpoint(2, 4));
    TEST_EXPECT(3 == midpoint(2, 5));
    TEST_EXPECT(4 == midpoint(2, 6));
}
