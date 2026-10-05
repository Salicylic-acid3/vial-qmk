# Keeb-On! Studio 用: Vial + OS 自動切り替え (users/salicylic_acid3/keebon_os.c)
# userspace (USER_NAME) の仕組みは環境によって users/ を見失うことがあるので、
# モジュールのソースを直接指定する
SRC += users/salicylic_acid3/keebon_os.c

SRC += quantum/os_detection.c
OS_DETECTION_ENABLE = yes

VIA_ENABLE = yes
VIAL_ENABLE = yes

TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
MAGIC_ENABLE = yes
GRAVE_ESC_ENABLE = yes
NKRO_ENABLE = yes

# TinyUF2 bootloader (Keeb-On! STM32G0 port) in the first 16 KB: the
# firmware starts at 0x08004000 and ships as a .uf2, copied onto the
# KEEBONBOOT drive. Boards without it use the multi-os-dfu keymap.
BOOTLOADER = tinyuf2
MCU_LDSCRIPT = STM32G0B1xB_tinyuf2
# No reset switch: hold the top-left key while plugging in for the
# bootloader (QK_BOOT and Keeb-On! Studio's update also get there).
BOOTMAGIC_ENABLE = yes
