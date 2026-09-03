/*
Copyright 2025 Salicylic_Acid

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

void board_init(void) {
    /* Keep USB FS on PA11/PA12 and disconnect the GPIO input pulls. */
    SYSCFG->CFGR1 &= ~(SYSCFG_CFGR1_PA11_RMP | SYSCFG_CFGR1_PA12_RMP);
    palSetPadMode(GPIOA, GPIOA_PIN11, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, GPIOA_PIN12, PAL_MODE_INPUT_ANALOG);

    RCC->APBENR1 |= RCC_APBENR1_CRSEN;
    (void)RCC->APBENR1;

    /* Select USB SOF as the CRS synchronization source. */
    CRS->CFGR =
        (CRS->CFGR & ~CRS_CFGR_SYNCSRC_Msk) |
        CRS_CFGR_SYNCSRC_1;

    /* Enable HSI48 automatic trimming and the frequency error counter. */
    CRS->CR |= CRS_CR_AUTOTRIMEN | CRS_CR_CEN;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9, KC_PSLS,
        KC_P4,   KC_P5,   KC_P6, KC_PAST,
        KC_P1,   KC_P2,   KC_P3, KC_PMNS,
        KC_P0, KC_PDOT, KC_PENT, KC_PPLS
    )
};