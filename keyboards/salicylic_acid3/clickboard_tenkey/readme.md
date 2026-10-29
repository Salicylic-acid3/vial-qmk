# ClickBoard Tenkey

![ClickBoard Tenkey](https://booth.pximg.net/1d33594d-0c5f-4f93-baf5-2e89e0d99afc/i/8890585/0da15e35-edf4-43e4-9e32-97dc8b985a91_base_resized.jpg)

Ultra-thin 19-key numpad of the ClickBoard series, with quiet thin micro switches. Also works as a macro pad.

* Keyboard Maintainer: [Salicylic-acid3](https://github.com/Salicylic-acid3)
* Hardware Supported: STM32G0B1
* Hardware Availability: [BOOTH](https://booth.pm/ja/items/8890585)
* About the ClickBoard series: https://salicylic-acid3.hatenablog.com/entry/clickboard-introduction

## Keymap and firmware

Change the keymap from the browser with [Keeb-On! Studio](https://keeb-on.studio/qmk) (or [Vial](https://get.vial.today/)).
The ready-built firmware for this keyboard is on the [download page](https://keeb-on.studio/qmk/downloads).

Make example for this keyboard (after setting up your build environment):

    make salicylic_acid3/clickboard_tenkey:multi-os

Flashing: put the keyboard into its bootloader (below); it shows up as a USB drive named `KEEBONBOOT`. Copy the `.uf2` file onto it.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader (a USB drive named `KEEBONBOOT`) in these ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Keyboards made before the `KEEBONBOOT` bootloader do not show up as a drive. Hold the BOOT switch while plugging in the keyboard to reach the chip's own DFU mode, and install the bootloader once as described on the [download page](https://keeb-on.studio/qmk/downloads).
