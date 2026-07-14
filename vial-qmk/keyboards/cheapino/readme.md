# cheapino

![cheapino](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Thomas Haukland](https://github.com/tompi)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make cheapino:default

Flashing example for this keyboard:

    make cheapino:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press `QK_BOOT` (Layer 7, A key — left pinky, middle row)

## Clearing EEPROM

Press `QK_CLEAR_EEPROM` (Layer 7, Z key — left pinky, bottom row). The device will not reboot automatically — press the controller button or disconnect power to apply the reset. The RGB underglow returning to **bright red** confirms the reset was successful.
