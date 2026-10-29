# InSixty EN

![InSixty EN](https://cdn-ak.f.st-hatena.com/images/fotolife/S/Salicylic_acid3/20250907/20250907054515.png)

60% split keyboard kit with an EN layout (Kailh Choc v2, no soldering).

* Keyboard Maintainer: [Salicylic-acid3](https://github.com/Salicylic-acid3)
* Hardware Supported: RP2040
* Hardware Availability: [Shop](https://salicylic-acid3.booth.pm/)
* Build guide: https://salicylic-acid3.hatenablog.com/entry/in60en-build-guide
* Build guide (case set): https://salicylic-acid3.hatenablog.com/entry/in60case-build-guide

## Keymap and firmware

Change the keymap from the browser with [Keeb-On! Studio](https://keeb-on.studio/qmk) (or [Vial](https://get.vial.today/)).
The ready-built firmware for this keyboard is on the [download page](https://keeb-on.studio/qmk/downloads).

Make example for this keyboard (after setting up your build environment):

    make salicylic_acid3/insixty_en:multi-os

Flashing example for this keyboard:

    make salicylic_acid3/insixty_en:multi-os:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader (a USB drive named `RPI-RP2`) in these ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Physical reset button**: Double-press the reset button on the PCB, if it has one
