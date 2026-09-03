#!/bin/bash
set -e
cd "$(dirname "$0")/.."
git apply --directory=lib/chibios patches/chibios-stm32g0b1.patch
cp patches/STM32G0B1xB.ld lib/chibios/os/common/startup/ARMCMx/compilers/GCC/ld/
echo "ChibiOS patched for STM32G0B1"
