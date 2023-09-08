Dumbphone 65C02 firmware
========================

This project contains the firmware for the 65C02 based dumb phone project.

This project works through an emulator on a Raspberry Pi Pico, and also on a
65C02 based board.

It supports communication with a cellular modem over a UART running Hayes like
commands. The cellular modem handles voice communication, but is controlled via
the 65C02 main board.

The firmware consists of three pieces: a boot loader, driver overlays, and the
application service. The boot loader is custom linked to load the driver
overlays from the first few sectors of an SD card. The rest of the SD card is
formatted with FAT16 based filesystems, the first of which acts as the firmware
filesystem. The application image is loaded from this first filesystem. The
FAT16 driver, as well as drivers relating to specific board setup, such as
serial I/O with the cellular modem, are loaded from the driver overlays.

Also included in this project are the virtual devices used through the emulator.
This allows the firmware to provide a basic HAL (hardware abstraction layer) for
communicating with the SD card and with serial devices. The boot loader is
custom linked with the specific hardware required for a particular board (bare
metal or emulated).

This firmware is written in symbolic 65C02 machine code, which is linked by the
[jlink65c02][jlink65c02] sister project. Another sister project,
[jemu65c02][jemu65c02], provides emulation of a 65C02 processor so that this
firmware can be run on alternative hardware.

[jlink65c02]: https://github.com/nanolith/jlink65c02
[jemu65c02]: https://github.com/nanolith/jemu65c02
