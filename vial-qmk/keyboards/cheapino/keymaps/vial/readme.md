# Vial Keymap for Cheapino

This is a Vial-optimized keymap based on the `musclememory` keymap. It provides full Vial GUI support for real-time keyboard configuration while maintaining the core functionality of the original.

## What is Vial?

[Vial](https://get.vial.today/) is an open-source cross-platform GUI application that allows you to configure your keyboard in real-time without needing to recompile firmware. It's a QMK fork that extends VIA with additional features like combos, tap dance, and more.

## Key Differences from `musclememory` Keymap

### What's the Same ✅
- **Layer RGB indicators** - Colors still change per layer
- **Base layer layout** - Same home row mods and key positions
- **All 8 layers** - Identical layer structure
- **Per-key tapping terms** - Custom timing for thumb keys
- **RGB color persistence** - Returns to your chosen color on base layer

### What's Different 🔄

1. **Standard RGB Keycodes**
   - Uses QMK standard `RGB_TOG`, `RGB_MOD`, `RGB_HUI`, etc.
   - These display correctly in Vial GUI
   - No custom M_RGB_* keycodes

2. **Simplified Thumb Cluster**
   - No complex tap dance on thumb keys
   - Simple layer taps: `LT(_L6, KC_ESC)`, `LT(_L5, KC_BSPC)`
   - Context menu key is just `KC_APP` (no tap dance toggle)

3. **GUI-Configurable Features**
   - **Tap Dance**: Configure up to 4 tap dance keys via Vial GUI
   - **Combos**: Configure up to 8 combos via Vial GUI
   - **Macros**: Create and edit macros in real-time
   - **Keymaps**: Change any key without recompiling

4. **Removed C-Defined Combos/Tap Dance**
   - Original keymap had hardcoded combos and tap dance in C
   - This version lets you configure them in the GUI instead

## Compiling

**Important:** This keymap requires the `vial-qmk` fork, not standard QMK.

### Setup

1. Clone vial-qmk (if you haven't already):
   ```bash
   git clone https://github.com/vial-kb/vial-qmk
   cd vial-qmk
   ```

2. Copy the `cheapino` keyboard folder to vial-qmk:
   ```bash
   cp -r /path/to/this/keyboards/cheapino vial-qmk/keyboards/
   ```

3. Compile:
   ```bash
   make cheapino:vial
   ```

4. Flash:
   ```bash
   make cheapino:vial:flash
   ```

## Using with Vial GUI

1. Download Vial from [get.vial.today](https://get.vial.today/)
2. Flash the compiled firmware to your keyboard
3. Open Vial - your keyboard should be automatically detected
4. **First time**: You'll need to unlock the keyboard using the security combo

### Security Unlock Combo

To access security-sensitive features (like flashing new firmware), you must press:

**Q + P** (top left + top right keys)

This protects against malicious software trying to flash your keyboard without your knowledge.

## Layer Colors

The RGB LED changes color based on the active layer:

| Layer | Color | Purpose |
|-------|-------|---------|
| Base (_L0) | Your custom color | Main typing layer |
| L1 | (inherit) | Reserved/unused |
| L2 | Red | Numpad layer |
| L3 | Cyan | Numbers & navigation |
| L4 | Lavender | Function keys |
| L5 | Amber | Navigation & editing |
| L6 | Mint | Mouse control |
| L7 | Pink | RGB & media controls |

## Configuring Tap Dance

In Vial GUI, go to the **Tap Dance** tab to configure:

- Single tap vs double tap actions
- Tap vs hold behavior
- Timing for each tap dance key

Example configurations you might want:
- Thumb key: Tap for Space, Hold for Layer
- ESC key: Double tap to clear all layers

## Configuring Combos

In Vial GUI, go to the **Combos** tab to configure key combinations:

Suggested combos from the original `musclememory` keymap:
- `V + Space` → Layer 7 (RGB controls)
- `M + Enter` → Layer 7 (RGB controls)
- `ESC + Backspace` → Toggle Layer 3
- `Q + W + E + T` → Bootloader (reflash mode)
- `Y + I + O + P` → Bootloader (reflash mode)
- `OSL(L4) + APP` → Caps Lock

## Layer Descriptions

### Base Layer
QWERTY with home row mods:
- Home row: Shift, Alt, Ctrl, GUI modifiers on holds
- Thumbs: Layer access and basic modifiers

### L2 - Numpad (Red)
Full numpad layout on right hand, operators on left.

### L3 - Numbers & Nav (Cyan)
Number row (1-9, 0) with arrow keys and symbols.

### L4 - Function Keys (Lavender)
F1-F24 function keys.

### L5 - Navigation (Amber)
Arrow keys, Home, End, Page Up/Down, editing keys.

### L6 - Mouse (Mint)
Mouse movement, buttons, and scroll wheels.

### L7 - System (Pink)
RGB controls, media keys, brightness controls.

## Encoder Support

The rotary encoder is configured as:
- **CW/CCW**: Mapped in the layout (shows as two round buttons in Vial)
- **Press**: Mute (on base layer)

You can remap the encoder actions per layer in Vial GUI.

## Troubleshooting

### Keyboard not detected in Vial
- Make sure you compiled with `vial-qmk`, not standard QMK
- Check that VIA/Vial support is enabled in device settings
- Try unplugging and replugging the keyboard

### Changes not saving
- Ensure you've unlocked the keyboard (Q + P combo)
- Check that EEPROM is not corrupted (reset in Vial settings)

### RGB not working
- Check that `RGBLIGHT_ENABLE` is set in your build
- Verify the LED is getting power
- Try toggling RGB with the Layer 7 controls

### Firmware too large
If the firmware doesn't fit, edit `rules.mk` and add:
```make
LTO_ENABLE = yes
VIAL_INSECURE = yes  # Removes security features
```

## Credits

- Original `musclememory` keymap: Custom home row mods layout
- Cheapino keyboard: Thomas Haukland (@tompi)
- Vial port: Adapted for GUI configuration
- License: GPL-2.0-or-later