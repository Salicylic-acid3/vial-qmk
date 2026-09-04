# STM32G0B1 support patch for Vial-QMK

Vial-QMK を STM32G0B1 系マイコンでビルドできるようにするパッチ一式です。

## 背景

本家 QMK は [qmk#24301](https://github.com/qmk/qmk_firmware/pull/24301) で STM32G0x1 に対応しました（コミット `f686ad9e6361e05fcfa78f453f90cd72181a7516` / 2025-05-19）。しかし Vial-QMK の `vial` ブランチはこの変更を取り込んでおらず、そのままでは STM32G0B1 を指定してもビルドできません。

このリポジトリでは以下の 2 層に分けて対応しています。

- **Vial-QMK 本体** — git 管理下なので通常のコミットに含まれる
- **ChibiOS サブモジュール** — git 管理外のため、このディレクトリのパッチで補う

## 対象

- MCU: **STM32G0B1CB**（フラッシュ 128KB / RAM 144KB / シングルバンク）
- ベース ChibiOS: `be44b3305f`

## ディレクトリの中身

| ファイル | 内容 |
|---|---|
| `chibios-stm32g0b1.patch` | ChibiOS の 2 ファイルへの差分 |
| `STM32G0B1xB.ld` | 128KB 版リンカスクリプト（ChibiOS に存在しないため新規作成） |
| `apply.sh` | 上記を適用するスクリプト |
| `README.md` | このファイル |

### chibios-stm32g0b1.patch の中身

**`os/hal/ports/STM32/STM32G0xx/hal_efl_lld.h`**

EFL（フラッシュを EEPROM 代わりに使うドライバ）のデバイス判定に `STM32G0B1xx` を追加します。これがないと `#error "This EFL driver does not support the selected device"` で停止します。

**`os/hal/ports/STM32/STM32G0xx/stm32_registry.h`**

G0B1 のフラッシュバンク数を 1 に変更します。G0B1CB は 128KB シングルバンク構成のため、デフォルトの 2 バンク前提のままだと EFL がバンク境界の計算を誤ります。

いずれも ChibiOS 本家フォーラムで作者（Stefan Kerkmann）が投稿し、本家に取り込まれた内容と同じものです。

## 適用手順

```bash
./patches/apply.sh
```

スクリプトがやっていること。

1. `lib/chibios` にパッチを適用
2. `STM32G0B1xB.ld` を ChibiOS のリンカスクリプト置き場へコピー

適用後、ビルドできます。

```bash
rm -rf .build
qmk compile -kb <keyboard> -km vial
```

## 適用が必要になるタイミング

ChibiOS サブモジュールへの変更は親リポジトリのコミットに含まれません。以下の操作で消えるので、その都度 `apply.sh` を実行してください。

- 新しい環境で `git clone` した直後
- `git submodule update` を実行したあと
- `lib/chibios` を別のコミットに切り替えたあと

適用済みかどうかは、リンカスクリプトの有無で判断できます。

```bash
ls lib/chibios/os/common/startup/ARMCMx/compilers/GCC/ld/ | grep G0B1xB
```

## Vial-QMK 本体側の変更

こちらはリポジトリにコミット済みなので、パッチの適用は不要です。参考までに変更内容を記載します。

### 変更したファイル

| ファイル | 内容 |
|---|---|
| `builddefs/common_features.mk` | wear_leveling の対象に `STM32G0xx` を追加 |
| `data/schemas/keyboard.jsonschema` | processor の enum に `STM32G0B1` |
| `lib/python/qmk/constants.py` | `CHIBIOS_PROCESSORS` と `MCU2BOOTLOADER` に追加 |
| `platforms/chibios/drivers/analog.c` | G0 の ADC 設定とピンマッピング（ADC 未使用なら省略可） |
| `platforms/chibios/mcu_selection.mk` | `STM32G0B1` のビルド定義ブロック |

### 追加したディレクトリ

`platforms/chibios/boards/GENERIC_STM32_G0B1XB/`

- `board/board.mk` — ChibiOS の `ST_NUCLEO64_G0B1RE` を参照
- `board/extra.c` — オプションバイト書き換え処理
- `configs/config.h` — ブートローダージャンプ設定
- `configs/mcuconf.h` — G0 向け ChibiOS 設定

## 注意事項

### 初回起動時にオプションバイトが書き換わります

`board/extra.c` は初回起動時に BOOT0 ピンと nRST ピンの設定をレガシー動作へ戻し、その直後にデバイスをリセットします。**USB が一瞬切れて再認識されますが正常な動作です。** 2 回目以降は通常どおり起動します。

この処理が走る前は物理 BOOT0 ピンが機能しないため、**最初の 1 回は SWD 経由での書き込みが必要になる場合があります。** 一度書き込めば、以降は DFU が使えます。

### 128KB 品以外は未検証

このパッチは G0B1CB（128KB シングルバンク）を前提としています。256KB 以上の品種はフラッシュのバンク構成に既知の問題があり、本家 QMK も 128KB 品に限定して対応しています。他の品種を使う場合は `STM32G0B1xB.ld` のメモリ定義を変更したうえで、EFL 周りの動作検証が別途必要です。

### 将来 Vial 本家が対応したら

Vial-QMK が STM32G0 に対応した時点で、このパッチ一式は不要になります。その際は本体側の変更とあわせて削除してください。

## 参考リンク

- [qmk/qmk_firmware#24301](https://github.com/qmk/qmk_firmware/pull/24301) — 本家 QMK の STM32G0x1 対応 PR
- [ChibiOS forum: STM32G0B1 Single bank flash support](https://forum.chibios.org/viewtopic.php?f=35&t=6471) — EFL 修正の議論
