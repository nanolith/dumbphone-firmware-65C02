cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0048 NEW)
PROJECT(dumb_phone_65c02 VERSION 0.0.1)

INCLUDE(CheckSymbolExists)

SET(CMAKE_MODULE_PATH $(CMAKE_MODULE_PATH) "${CMAKE_SOURCE_DIR}/cmake/Modules")

#minunit package
find_package(minunit REQUIRED)

#jemu65c02 package
find_package(jemu65c02 REQUIRED)

#jlink65c02 package
find_package(jlink65c02 REQUIRED)

#source files
AUX_SOURCE_DIRECTORY(src/demo_phone/virtual_devices DEMO_PHONE_VIRTUAL_SOURCES)

#test source files
AUX_SOURCE_DIRECTORY(
    test/demo_phone/virtual_devices DEMO_PHONE_VIRTUAL_TEST_SOURCES)

ADD_LIBRARY(demophone_virtual_devices STATIC ${DEMO_PHONE_VIRTUAL_SOURCES})
TARGET_COMPILE_OPTIONS(
    demophone_virtual_devices
        PRIVATE -O3 -fPIC ${JEMU65C02_CFLAGS} -Wall -Werror -Wextra -Wpedantic
                -Wno-unused-command-line-argument)

ADD_EXECUTABLE(
    testdemophone_virtual_devices ${DEMO_PHONE_VIRTUAL_SOURCES}
        ${DEMO_PHONE_VIRTUAL_TEST_SOURCES})
TARGET_COMPILE_OPTIONS(
    testdemophone_virtual_devices PRIVATE -g -O0 --coverage ${MINUNIT_CFLAGS}
        ${JEMU65C02_CFLAGS} -Wall -Werror -Wextra -Wpedantic
        -Wno-unused-command-line-argument)
TARGET_LINK_LIBRARIES(
    testdemophone_virtual_devices PRIVATE -g -O0 --coverage ${MINUNIT_LDFLAGS})
set_source_files_properties(
    ${DEMO_PHONE_VIRTUAL_TEST_SOURCES} PROPERTIES COMPILE_FLAGS "${STD_CXX_20}")

ADD_CUSTOM_TARGET(
    test
    COMMAND testdemophone_virtual_devices
    DEPENDS testdemophone_virtual_devices)
