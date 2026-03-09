# Cheapino Keymap Comparison Guide

This document compares the two available keymaps for the Cheapino keyboard: `musclememory` and `vial`.

## Quick Comparison Table

| Feature | musclememory | vial |
|---------|-------------|------|
| **Framework** | Standard QMK | Vial (QMK fork) |
| **Configuration** | Compile-time only | Real-time via GUI |
| **RGB Layer Indicators** | ✅ Yes | ✅ Yes |
| **Custom RGB Keycodes** | ✅ Custom (M_RGB_*) | ⚠️ Standard (RGB_*) |
| **Tap Dance** | ✅ C-defined (1 complex) | ✅ GUI-configurable (4 slots) |
| **Combos** | ✅ C-defined (7 combos) | ✅ GUI-configurable (8 slots) |
| **Thumb Cluster** | Complex tap dance | Simple layer taps |
| **Macros** | ⚠️ Limited | ✅ Full GUI editor |
| **Keymap Changes** | Requires recompile | ✅ Real-time in GUI |
| **Firmware Size** | Smaller | Larger (VIA overhead) |
| **Repository** | qmk/qmk_firmware | vial-kb/vial-qmk |

## Detailed Comparison

### musclememory Keymap

**Philosophy:** Feature-rich, highly customized QMK firmware with everything configured in C code.

#### Advantages ✅
- **Complete control** - Everything defined in code
- **Complex tap dance** - Sophisticated thumb key behavior with context awareness
- **Custom RGB keycodes** - Works around hardware conflicts
- **Smaller firmware** - No VIA/Vial overhead
- **Standard QMK** - Works with official QMK repository
- **Proven stability** - No dynamic configuration to potentially corrupt

#### Features
1. **Custom Tap Dance on Menu Key**
   - Base layer: Single tap/hold = Context Menu | Double tap = Toggle L2
   - Other layers: Any interaction = Return to base layer
   - 350ms timing window

2. **Advanced Thumb Keys**
   - `TD(TD_CMENU)` - Context menu with layer toggle
   - Four thumb keys with tap dance: ESC, Space, Enter, Backspace
   - Each has different tap vs hold behavior

3. **Custom RGB Implementation**
   - Custom keycodes (M_RGB_TOG, M_RGB_MOD, etc.)
   - Avoids conflicts with specific hardware drivers
   - Color capture and restore on layer changes

4. **7 Hardcoded Combos**
   - V+Space / M+Enter → Layer 7 (RGB controls)
   - ESC+Backspace → Toggle Layer 3
   - Q+W+E+T / Y+I+O+P → Bootloader mode
   - OSL(L4)+TD(CMENU) → Caps Lock

5. **Advanced Timing**
   - Per-key tapping terms (200-350ms)
   - Post-processing for layer clears

#### Best For
- Users who want maximum customization
- Those comfortable editing C code
- People who prefer compiled, unchanging firmware
- Advanced QMK users who want full control
- Those using official QMK tooling

### vial Keymap

**Philosophy:** GUI-first approach with real-time configuration while maintaining core functionality.

#### Advantages ✅
- **No compilation needed** - Change anything via GUI
- **Visual configuration** - See your keyboard layout
- **Easy experimentation** - Try changes instantly
- **Portable config** - Save/load configurations
- **Beginner friendly** - No coding required
- **Cross-platform GUI** - Windows, Mac, Linux

#### Features
1. **Standard RGB Keycodes**
   - Uses QMK standard RGB_TOG, RGB_MOD, RGB_HUI, etc.
   - Display correctly in Vial GUI
   - Fully configurable placement

2. **Simplified Thumb Cluster**
   - Simple layer taps: `LT(_L6, KC_ESC)`, `LT(_L5, KC_BSPC)`
   - No complex tap dance (configure via GUI if needed)
   - `KC_APP` for context menu (simple key)

3. **GUI-Configurable Tap Dance**
   - 4 tap dance slots available
   - Configure timing, actions per slot
   - Visual editor in Vial app

4. **GUI-Configurable Combos**
   - 8 combo slots available
   - Click keys to create combos
   - Instant testing

5. **Same Layer Colors**
   - Identical RGB layer indicators
   - Color persistence on base layer
   - All color definitions maintained

#### Best For
- Users new to QMK/custom keyboards
- Those who like to experiment with layouts
- People who don't want to compile firmware
- Users who change keymaps frequently
- Anyone wanting a visual configuration tool

## What's Identical Between Both

### Layer Structure
Both keymaps have the same 8 layers:
- **L0 (Base)**: QWERTY with home row mods
- **L1**: Reserved/unused
- **L2**: Numpad (Red LED)
- **L3**: Numbers & navigation (Cyan LED)
- **L4**: Function keys (Lavender LED)
- **L5**: Navigation & editing (Amber LED)
- **L6**: Mouse control (Mint LED)
- **L7**: RGB & media controls (Pink LED)

### Core Features
- Home row mods (Shift, Alt, Ctrl, GUI)
- RGB layer color indicators
- Encoder support (mute on press)
- Per-key tapping term customization
- All layer key positions

## Migration Path

### From musclememory to vial

If you're currently using `musclememory` and want to try `vial`:

1. **Backup your current firmware** (you can always go back)
2. **Set up vial-qmk** repository
3. **Flash the vial keymap**
4. **Clear EEPROM**

### From vial to musclememory

If you want more control or a smaller firmware:

1. **Document your Vial configuration** (screenshot/export if possible)
2. **Flash musclememory keymap**
3. **Modify C code** to add any custom combos/macros you created
4. **Recompile and flash**

## Which Should You Choose?

### Choose `musclememory` if you:
- Want maximum firmware control
- Prefer code-based configuration
- Need the sophisticated tap dance behavior
- Use official QMK repository/tooling
- Want smaller firmware size
- Rarely change your keymap
- Are comfortable with C programming

### Choose `vial` if you:
- Want to configure via GUI
- Experiment with layouts frequently
- Are new to QMK
- Don't want to set up compilation environment
- Like visual feedback when configuring
- Want to save/load different configurations
- Prefer standard QMK keycodes

## Can I Use Both?

**Yes!** You can:
1. Keep both keymaps in your repository
2. Compile either one as needed (vial-qmk can compile both)
3. Flash different versions to test
4. Switch between them anytime

The keymaps are independent and don't interfere with each other.

## Technical Notes

### Firmware Size
- **musclememory**: ~18-22KB (approximate)
- **vial**: ~24-28KB (approximate)

The RP2040 on Cheapino has plenty of space (256KB flash), so size shouldn't be a concern for either keymap.

### EEPROM Usage
- **musclememory**: Only stores QMK settings
- **vial**: Stores dynamic keymap, combos, tap dance, macros

If you switch between keymaps frequently, you may want to reset EEPROM.

### Compatibility
- **musclememory**: Any QMK-compatible tool (QMK Toolbox, CLI)
- **vial**: Requires Vial GUI for configuration (firmware flashing still uses standard tools)

## Support & Resources

### musclememory Keymap
- File: `keyboards/cheapino/keymaps/musclememory/keymap.c`
- Modify: Edit the C code directly
- Compile: `make cheapino:musclememory`
- Documentation: QMK docs (docs.qmk.fm)

### vial Keymap
- File: `keyboards/cheapino/keymaps/vial/keymap.c`
- Configure: Vial GUI application
- Compile: `make cheapino:vial` (in vial-qmk)
- Documentation: get.vial.today/docs/
- README: `keyboards/cheapino/keymaps/vial/readme.md`

## Conclusion

Both keymaps offer excellent functionality for the Cheapino keyboard:

- **musclememory** is for power users who want complete control and sophisticated features defined in code
- **vial** is for users who want the convenience of GUI configuration without sacrificing core functionality

There's no wrong choice - pick the one that matches your workflow and preferences!
