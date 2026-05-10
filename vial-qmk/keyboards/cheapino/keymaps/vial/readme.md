# Cheapino Vial Configuration

This firmware implements the [Muscle-memory-friendly home row mods layout](https://blog.getreu.net/20250826-muscle-memory-friendly-home-row-mods/). All defaults can be customized via [Vial](https://get.vial.today/).

## Compiling and Flashing

1.  **Clone and Setup:**
    ```bash
    git clone https://github.com/vial-kb/vial-qmk
    cd vial-qmk
    git submodule update --init --recursive
    ```

3.  **Compile:**
    ```bash
    make cheapino:vial
    ```

4.  **Flash to Cheapino (RP2040)**:
    *   **Method 1 (Physical Button):** Hold the **BOOTSEL button** on the RP2040 controller while
        plugging in the USB cable.
    *   **Method 2 (Keycode):** Hold the middle thumb key on the left side and press the rotary knob.
    *   Drag and drop the `.uf2` file onto the `RPI-RP2` drive.



## Clearing EEPROM

Clearing the EEPROM resets all persistent settings (RGB configurations, Vial keymaps, tap dances, and combos) to the firmware defaults.

In this firmware, the clear function is hard-mapped to specific keys to enable a reset without the GUI:

1.  **Keycode Position:**
    *   **Layer 5:** The **Rotary Encoder Press** (the physical button between the halves).
2.  **Accessing the Layer:**
    *   **Layer 5:** Hold the **Backspace** thumb key on the right half.
3.  **Triggering the Reset:**
    *   **Via Layer 5:** Hold the **Backspace** key and press the **Rotary Encoder** down.
4.  **Verification:**
    The device will not automatically reboot. To confirm that the reset was successful, watch for the RGB underglow to return to the default color **a bright red**.



## RGB Lighting & Layer Feedback

The underglow changes color based on the active layer:

| Layer | Color | Purpose |
|-------|-------|-------|
| Base (L0) | Custom | Main layer (restores the last saved color) |
| L1 | (inherit) | Reserved / Unused |
| L2 | Red | Numpad Layer |
| L3 | Cyan | Numbers & Navigation |
| L4 | Lavender | Function keys (F1-F24) |
| L5 | Amber | Navigation & Editing |
| L6 | Mint | Mouse control |
| L7 | Pink | RGB & Media control |

If wished for, the LEDs can be turned off for all layers (`RGB_TOG` on layer 7),
or for the base layer only (`RGB_VAD` on layer 7).




## Using Vial GUI

1.  **Download:** Download Vial from [get.vial.today](https://get.vial.today/).
2.  **Security Unlock:** To change security-relevant settings, you must press the **Security Unlock Combo**: **Q + P** (top-left key + top-right key).
3.  **Configuration:** Use the tabs for **Tap Dance** and **Combos** to customize the layout.


## Troubleshooting

*   **Not recognized:** Ensure that you compiled with `vial-qmk`.
*   **Not saving:** Check if the keyboard was unlocked with **Q + P**.
*   **Firmware too large:** Activate `LTO_ENABLE = yes` in the `rules.mk`.\
    The `cheapino` uses an RP2040, which has limited flash memory.

## Credits

*   **Original muscle-memory keymap:** Custom home-row-mods layout by Jens Getreu.
*   **Cheapino keyboard:** Thomas Haukland (@tompi).
