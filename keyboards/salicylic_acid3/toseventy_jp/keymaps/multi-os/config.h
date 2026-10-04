/* Copyright 2021 Salicylic_acid3
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

/* Select hand configuration */

#define VIAL_KEYBOARD_UID {0x22, 0x5C, 0x35, 0x30, 0xC5, 0xB5, 0x57, 0xA7}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

/* 3 ブロック x 4 レイヤー (Keeb-On! Studio の OS 切り替え用) */
/* keyboard.json の dynamic_keymap.layer_count より優先させる */
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 12
#define KEEBON_OS_LAYERS_PER_BLOCK 4
#define KEEBON_OS_BLOCK_COUNT 3
