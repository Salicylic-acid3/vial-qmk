# Bootloaders

## tinyuf2-stm32g0b1.bin

TinyUF2 for the STM32G0B1 keyboards (ClickBoard Tenkey, EzTenkey, EzTenkeyMX,
WzTwenty STM). Built from the STM32G0 port of adafruit/tinyuf2
(`ports/stm32g0`, board `salicylic_g0b1`): 16 KB at 0x08000000, USB
355D:101A, drive name KEEBONBOOT, write-protects itself on first start.

Install once over the chip's own DFU (hold BOOT0 while plugging in):

    dfu-util -a 0 -d 0483:DF11 -s 0x08000000:mass-erase:force:leave -D tinyuf2-stm32g0b1.bin

then copy the keyboard's `.uf2` onto the KEEBONBOOT drive. The release
workflow publishes this file next to the firmware.
