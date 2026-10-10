# cheapino

A column-staggered 3x5+3 split keyboard (RP2040), running the [muscle memory
friendly home row mods](https://blog.getreu.net/20250826-muscle-memory-friendly-home-row-mods/)
layout. See the repository root [README.md](../../../README.md) for the
project this keymap belongs to.

* Keyboard Maintainer: [Thomas Haukland](https://github.com/tompi) (hardware)
* Hardware Supported: Cheapino v2, RP2040
* Keymaps: `musclememory` (compiled-in layout) and `vial` (Vial-reconfigurable)
  -- there is no `default` keymap in this fork, it was removed upstream.

Build example:

    make cheapino:musclememory
    make cheapino:vial

Flashing: hold the reset button while plugging in USB, then drag the
resulting `.uf2` onto the `RPI-RP2` drive that appears. See each keymap's own
readme (`keymaps/musclememory/readme.md`, `keymaps/vial/readme.md`) for the
full build/flash/EEPROM-reset procedure.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press `QK_BOOT` (Layer 7, Q key — left pinky, top row)

## Clearing EEPROM

Press `QK_CLEAR_EEPROM` (Layer 7, W key — left ring, top row). The device will not reboot automatically — press the controller button or disconnect power to apply the reset. The RGB underglow returning to **bright red** confirms the reset was successful.
