# Combo Configuration - Complete Solution

## Summary

The Cheapino Vial keymap now includes **6 pre-configured default combos** that load automatically when EEPROM is initialized. This document explains how they work and how to troubleshoot if they're not triggering.

## The Issue: Combos Not Triggering

If you flash the firmware and combos don't work, there are typically two reasons:

### 1. EEPROM Wasn't Reset (Most Common)

**Problem**: Default combos are set in `eeconfig_init_user()`, which **only runs when EEPROM is initialized**, not on every boot.

**Solution**: Force an EEPROM reset (see below).

### 2. Wrong Keycode Types in Combo Definitions

**Problem**: Using mod-tap keycodes like `LGUI_T(KC_SPC)` instead of base keycodes like `KC_SPC`.

**Solution**: Fixed in the code - combos now use base keycodes only.

## Default Combos Included

| Slot | Keys | Action | Result |
|------|------|--------|--------|
| **0** | Space + Enter | `MO(7)` | Activate Layer 7 (RGB/Media) |
| **1** | V + Space | `MO(7)` | Layer 7 from left hand |
| **2** | M + Enter | `MO(7)` | Layer 7 from right hand |
| **3** | ESC + Backspace | `TG(3)` | Toggle numbers/nav layer |
| **4** | Q+W+E+T | `QK_BOOT` | Bootloader (left hand) ⚠️ |
| **5** | Y+I+O+P | `QK_BOOT` | Bootloader (right hand) ⚠️ |
| **6** | (empty) | - | Available for customization |
| **7** | (empty) | - | Available for customization |

⚠️ **Warning**: Bootloader combos immediately enter flashing mode!

## How to Activate Default Combos

Defaults only load when EEPROM is initialized. Use one of these methods:

### Method 1: Via Bootloader Combo (Recommended)

1. **Press Q+W+E+T together** (or Y+I+O+P on right hand)
2. Keyboard enters bootloader mode (appears as USB drive)
3. **Copy `cheapino_vial.uf2`** to the drive
4. Keyboard reboots and **EEPROM resets automatically**
5. **Test immediately**: Press Space+Enter together
6. **Expected result**: LED turns pink (Layer 7 activated)

### Method 2: Via BOOTSEL Button

1. Unplug keyboard
2. Hold **BOOTSEL button** on RP2040
3. Plug in keyboard while holding BOOTSEL
4. Release BOOTSEL (keyboard is now in bootloader mode)
5. Copy `cheapino_vial.uf2` to the USB drive
6. Keyboard reboots with fresh EEPROM
7. Test combos immediately

### Method 3: Via Vial GUI

1. Open Vial application
2. Go to **Settings** or **Security** tab
3. Click **"Reset EEPROM"**
4. Confirm the reset
5. **Unplug and replug** keyboard
6. Open Vial → **Combos tab** → should now show configured combos
7. Test Space+Enter combo

## Testing Combos

### Quick Test: Space + Enter

1. Open a text editor
2. Press **Space alone** → types a space ✓
3. Press **Enter alone** → types enter ✓
4. Press **both together quickly** (within 50ms)
5. **Expected**: RGB LED changes to **pink** (Layer 7 active)
6. While holding combo: Press keys on top row right side
7. **Expected**: RGB controls work (toggle, mode, brightness)

### Test: V + Space

1. Type 'v' alone → outputs 'v' ✓
2. Press Space alone → outputs space ✓
3. Press **V + Space together**
4. **Expected**: LED turns pink (Layer 7)

### Test: ESC + Backspace

1. Press ESC alone → outputs ESC ✓
2. Press Backspace alone → deletes character ✓
3. Press **both together**
4. **Expected**: LED turns **cyan** (Layer 3 toggled on)
5. Press combo again → LED returns to base color (Layer 3 off)

## Why It Works Now

### Fixed Issues

1. **Enabled `COMBO_ENABLE` in keyboard.json**
   ```json
   "features": {
       "combo": true  // Was false, now true
   }
   ```

2. **Used base keycodes instead of mod-tap keycodes**
   ```c
   // ❌ Wrong (was using this):
   combo.input[0] = LGUI_T(KC_SPC);
   
   // ✅ Correct (fixed to this):
   combo.input[0] = KC_SPC;
   ```

3. **Proper initialization sequence**
   ```c
   void eeconfig_init_user(void) {
       // Set all combos...
       vial_init();  // Reload combos to activate
   }
   ```

## How Defaults Work

### Initialization Flow

```
Flash Firmware
    ↓
First Boot
    ↓
EEPROM Uninitialized?
    ↓ YES
eeconfig_init_user() runs
    ↓
Default combos written to EEPROM
    ↓
vial_init() reloads combos
    ↓
Combos active! ✓
```

### Subsequent Boots

```
Reboot Keyboard
    ↓
EEPROM Already Initialized
    ↓
Load existing combos from EEPROM
    ↓
User customizations preserved ✓
```

### Key Points

- ✅ Defaults load **once** on EEPROM initialization
- ✅ User changes via Vial GUI **persist** across reboots
- ✅ Defaults **don't overwrite** user customizations
- ✅ Can restore defaults by **resetting EEPROM**

## Troubleshooting Checklist

If combos still don't work:

- [ ] Did you reset EEPROM? (Required for defaults to load)
- [ ] Open Vial → Combos tab → Are combos listed? (If empty, EEPROM wasn't reset)
- [ ] Are you **tapping** keys quickly? (Not holding them)
- [ ] Press keys **simultaneously** (within 50ms window)
- [ ] Are you on **Layer 0** (base layer)?
- [ ] Firmware compiled correctly? (Check for errors)

## Common Mistakes

### Mistake 1: Not Resetting EEPROM

**Symptom**: Reflashed firmware but combos don't work.

**Cause**: `eeconfig_init_user()` only runs on EEPROM reset, not reflash.

**Fix**: Use one of the EEPROM reset methods above.

### Mistake 2: Holding Mod-Tap Keys

**Symptom**: Sometimes works, sometimes doesn't.

**Cause**: Holding Space sends GUI modifier, not Space keycode.

**Fix**: **Tap** both keys quickly, don't hold.

### Mistake 3: Keys Not Simultaneous Enough

**Symptom**: Each key outputs individually, combo never triggers.

**Cause**: Keys pressed more than 50ms apart.

**Fix**: Press more simultaneously, or increase combo term in Vial GUI.

## Customization

### Via Vial GUI (No Recompile Needed)

1. Open Vial application
2. Go to **Combos** tab
3. Select any slot (0-7)
4. Click keys on virtual keyboard to add them
5. Set output action in dropdown
6. Changes save automatically to EEPROM

### Via Code (Requires Recompile)

Edit `keymap.c`, modify `eeconfig_init_user()`:

```c
void eeconfig_init_user(void) {
    // Add your custom combo
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = KC_A;      // Your key 1
        combo.input[1] = KC_S;      // Your key 2
        combo.output = KC_ESC;      // Your action
        dynamic_keymap_set_combo(0, &combo);
    }
    
    vial_init();  // Don't forget this!
}
```

Then recompile: `make cheapino:vial`

## Important Notes

### Base Keycodes Required

Always use base keycodes in combo definitions:

| Keymap Position | Keymap Definition | Combo Uses |
|----------------|-------------------|------------|
| Middle thumb | `LGUI_T(KC_SPC)` | `KC_SPC` |
| Right middle thumb | `LGUI_T(KC_ENT)` | `KC_ENT` |
| V key | `RGUI_T(KC_V)` | `KC_V` |
| ESC key | `LT(_L6, KC_ESC)` | `KC_ESC` |

### Timing

- Default combo term: **50ms**
- Keys must be pressed within this window
- Adjustable per-combo in Vial GUI (try 75-100ms if needed)

### Limitations

- Maximum **4 keys** per combo
- Total **8 combo slots** available
- Keycodes must match exactly (layer-dependent)

## Related Documentation

- **`COMBO_SETUP_GUIDE.md`** - How to configure combos in Vial GUI
- **`COMBOS_QUICKSTART.md`** - Quick reference guide
- **`DEFAULT_COMBOS.md`** - Technical details about defaults
- **`VIAL_DEFAULTS_ANSWER.md`** - How Vial defaults work
- **`COMBO_TROUBLESHOOTING.md`** - Detailed troubleshooting steps

## Success Criteria

Your combos are working correctly if:

1. ✅ Space+Enter → LED turns pink (Layer 7)
2. ✅ V+Space → LED turns pink (Layer 7)
3. ✅ M+Enter → LED turns pink (Layer 7)
4. ✅ ESC+Backspace → LED turns cyan (Layer 3 toggle)
5. ✅ Vial GUI Combos tab shows configured combos
6. ✅ Q+W+E+T → Enters bootloader mode

If all of the above work: **You're done!** 🎉

If not: See `COMBO_TROUBLESHOOTING.md` for detailed help.

---

**Last Updated**: March 2024  
**Firmware**: cheapino_vial.uf2 (109KB)  
**Vial Version**: 0.7+