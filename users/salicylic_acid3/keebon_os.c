// Copyright 2026 Salicylic-acid3 (@Salicylic-acid3)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keebon_os.h"
#include "os_detection.h"
#include "eeconfig.h"
#include "via.h"

// ---- EEPROM レイアウト (eeconfig kb 32bit) ----
//   bit 0-1  : mode
//   bit 2-3  : Windows のブロック
//   bit 4-5  : macOS  のブロック
//   bit 6-7  : Linux  のブロック
//   bit 8-9  : 判定不能時のブロック
//   bit 24-31: magic (未初期化判定)
#define KEEBON_MAGIC 0x4B
#define KEEBON_MAGIC_SHIFT 24

typedef struct {
    uint8_t mode;
    uint8_t block[KEEBON_TGT_COUNT];
} keebon_os_config_t;

static keebon_os_config_t cfg;
static os_variant_t       detected      = OS_UNSURE;
static int8_t             preview_block = -1;
static uint8_t            active_block  = 0;

static void config_defaults(void) {
    cfg.mode                     = KEEBON_MODE_AUTO;
    cfg.block[KEEBON_TGT_WINDOWS] = 0;
    cfg.block[KEEBON_TGT_MACOS]   = 1;
    cfg.block[KEEBON_TGT_LINUX]   = 2;
    cfg.block[KEEBON_TGT_OTHER]   = 0;
}

static uint8_t clamp_block(uint8_t b) {
    return (b < KEEBON_OS_BLOCK_COUNT) ? b : 0;
}

static void config_save(void) {
    uint32_t raw = 0;
    raw |= (uint32_t)(cfg.mode & 0x3);
    for (uint8_t i = 0; i < KEEBON_TGT_COUNT; i++) {
        raw |= (uint32_t)(cfg.block[i] & 0x3) << (2 + 2 * i);
    }
    raw |= (uint32_t)KEEBON_MAGIC << KEEBON_MAGIC_SHIFT;
    eeconfig_update_kb(raw);
}

static void config_load(void) {
    uint32_t raw = eeconfig_read_kb();
    if (((raw >> KEEBON_MAGIC_SHIFT) & 0xFF) != KEEBON_MAGIC) {
        config_defaults();
        config_save();
        return;
    }
    cfg.mode = raw & 0x3;
    for (uint8_t i = 0; i < KEEBON_TGT_COUNT; i++) {
        cfg.block[i] = clamp_block((raw >> (2 + 2 * i)) & 0x3);
    }
}

static uint8_t target_for_os(os_variant_t os) {
    switch (os) {
        case OS_WINDOWS: return KEEBON_TGT_WINDOWS;
        case OS_MACOS:
        case OS_IOS:     return KEEBON_TGT_MACOS;
        case OS_LINUX:   return KEEBON_TGT_LINUX;
        default:         return KEEBON_TGT_OTHER;
    }
}

static uint8_t resolve_block(void) {
    if (preview_block >= 0) return clamp_block(preview_block);
    switch (cfg.mode) {
        case KEEBON_MODE_WINDOWS: return cfg.block[KEEBON_TGT_WINDOWS];
        case KEEBON_MODE_MACOS:   return cfg.block[KEEBON_TGT_MACOS];
        case KEEBON_MODE_LINUX:   return cfg.block[KEEBON_TGT_LINUX];
        default:                  return cfg.block[target_for_os(detected)];
    }
}

static void apply_block(uint8_t b) {
    b            = clamp_block(b);
    active_block = b;
    default_layer_set((layer_state_t)1 << (b * KEEBON_OS_LAYERS_PER_BLOCK));
    layer_clear();
}

uint8_t keebon_os_active_block(void) {
    return active_block;
}

void keebon_os_refresh(void) {
    apply_block(resolve_block());
}

// ---- QMK フック ----

void eeconfig_init_user(void) {
    config_defaults();
    config_save();
}

void keyboard_post_init_user(void) {
    config_load();
    detected = detected_host_os(); // 既に判定済みならそれを使う
    keebon_os_refresh();
}

// 判定が確定した瞬間に呼ばれる (起動後の待ち時間は不要)
bool process_detected_host_os_user(os_variant_t os) {
    detected = os;
    keebon_os_refresh();
    return true;
}

// ---- Keeb-On! Studio との通信 (VIA keyboard_value の独自 id) ----
//
// get 0x80 の応答 (data[2] 以降):
//   [0] protocol  [1] detected_os (os_variant_t)  [2] mode  [3] active_block
//   [4] blk_windows [5] blk_macos [6] blk_linux [7] blk_other
//   [8] layers_per_block [9] block_count [10] preview_block (0xFF = なし)
// set 0x80 の引数 (data[2] 以降):
//   [0] mode [1] blk_windows [2] blk_macos [3] blk_linux [4] blk_other
// set 0x81 の引数:
//   [0] block (0xFF で解除)

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    uint8_t *cmd = &data[0];
    uint8_t  vid = data[1];
    uint8_t *arg = &data[2];

    if (*cmd == id_get_keyboard_value && vid == KEEBON_VAL_OS) {
        arg[0]  = KEEBON_OS_PROTOCOL;
        arg[1]  = (uint8_t)detected;
        arg[2]  = cfg.mode;
        arg[3]  = active_block;
        arg[4]  = cfg.block[KEEBON_TGT_WINDOWS];
        arg[5]  = cfg.block[KEEBON_TGT_MACOS];
        arg[6]  = cfg.block[KEEBON_TGT_LINUX];
        arg[7]  = cfg.block[KEEBON_TGT_OTHER];
        arg[8]  = KEEBON_OS_LAYERS_PER_BLOCK;
        arg[9]  = KEEBON_OS_BLOCK_COUNT;
        arg[10] = (preview_block >= 0) ? (uint8_t)preview_block : 0xFF;
        return;
    }

    if (*cmd == id_set_keyboard_value && vid == KEEBON_VAL_OS) {
        cfg.mode = arg[0] & 0x3;
        for (uint8_t i = 0; i < KEEBON_TGT_COUNT; i++) {
            cfg.block[i] = clamp_block(arg[1 + i]);
        }
        config_save();
        keebon_os_refresh();
        return;
    }

    if (*cmd == id_set_keyboard_value && vid == KEEBON_VAL_OS_PREVIEW) {
        preview_block = (arg[0] == 0xFF) ? -1 : (int8_t)clamp_block(arg[0]);
        keebon_os_refresh();
        return;
    }

    *cmd = id_unhandled;
}
