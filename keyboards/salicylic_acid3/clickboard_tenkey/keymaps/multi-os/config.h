/* Copyright 2026 Salicylic_acid3
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* 3 ブロック x 4 レイヤー (Keeb-On! Studio の OS 切り替え用) */
#define DYNAMIC_KEYMAP_LAYER_COUNT 12
#define KEEBON_OS_LAYERS_PER_BLOCK 4
#define KEEBON_OS_BLOCK_COUNT 3

#define VIAL_KEYBOARD_UID {0x8D, 0x99, 0xFA, 0x18, 0xA5, 0x5D, 0x72, 0xE4}
/* NumLock + 0 を押し続けるとアンロック */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 4 }

#define NUM_LOCK_LED_PIN A6

// Active Low（Low=点灯）の設定
#define LED_PIN_ON_STATE 0
