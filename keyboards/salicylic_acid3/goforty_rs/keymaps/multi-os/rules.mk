# Keeb-On! Studio 用: Vial + OS 自動切り替え (users/salicylic_acid3/keebon_os.c)
# userspace (USER_NAME) の仕組みは環境によって users/ を見失うことがあるので、
# モジュールのソースを直接指定する
SRC += users/salicylic_acid3/keebon_os.c

SRC += quantum/os_detection.c
OS_DETECTION_ENABLE = yes

VIA_ENABLE = yes
VIAL_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
