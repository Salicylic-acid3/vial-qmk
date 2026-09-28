// Copyright 2026 Salicylic-acid3 (@Salicylic-acid3)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Keeb-On! Studio 用 OS 自動切り替えモジュール
//
// レイヤーを「ブロック」に分け、検出したホスト OS ごとに使うブロックを切り替える。
//   ブロック A = レイヤー 0..3, ブロック B = 4..7, ブロック C = 8..11 (既定)
// 設定 (固定モード / OS→ブロックの割り当て) は EEPROM に保存し、
// VIA の keyboard_value コマンド経由で Keeb-On! Studio から読み書きする。

#pragma once

#include "quantum.h"

#ifndef KEEBON_OS_LAYERS_PER_BLOCK
#    define KEEBON_OS_LAYERS_PER_BLOCK 4
#endif
#ifndef KEEBON_OS_BLOCK_COUNT
#    define KEEBON_OS_BLOCK_COUNT 3
#endif

// GUI に返すプロトコル版。フォーマットを変えたら上げる
#define KEEBON_OS_PROTOCOL 1

// VIA id_get_keyboard_value / id_set_keyboard_value の value id (0x80 以降は独自)
#define KEEBON_VAL_OS 0x80         // get: 状態と設定を返す / set: 設定を保存して適用
#define KEEBON_VAL_OS_PREVIEW 0x81 // set: 一時的にブロックを切り替え (0xFF で解除、保存しない)

// 固定モード
enum keebon_os_mode {
    KEEBON_MODE_AUTO = 0,
    KEEBON_MODE_WINDOWS,
    KEEBON_MODE_MACOS,
    KEEBON_MODE_LINUX,
};

// 割り当て先 OS (iOS は macOS として扱う)
enum keebon_os_target {
    KEEBON_TGT_WINDOWS = 0,
    KEEBON_TGT_MACOS,
    KEEBON_TGT_LINUX,
    KEEBON_TGT_OTHER, // 判定できなかったとき
    KEEBON_TGT_COUNT,
};

uint8_t keebon_os_active_block(void);
void    keebon_os_refresh(void);
