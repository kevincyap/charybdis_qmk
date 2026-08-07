# Charybdis (3x5) `via` keymap

The Charydbis (3x5) `via` keymap is based on a QWERTY layout with [home row mods](https://precondition.github.io/home-row-mods) and [Miryoku-inspired layers](https://github.com/manna-harbour/miryoku), and some features and changes specific to the Charybdis.

This layout supports RGB matrix. However, due to space constraints on the MCU, only a limited number of effect can be enabled at once. Look at the `config.h` file and enable your favorite effect.

This layout also supports VIA.

## Customizing the keymap

### Caps Word combo

Press the home-row `F` key and the left inner `Tab` thumb key together within
50 ms to toggle Caps Word. The combo is active only on the base layer. Holding
either Shift while pressing the combo toggles Caps Lock instead.

After first flashing a build containing this combo, run `EE_CLR` once so Argos
copies the compiled combo into its editable EEPROM configuration.

### Dynamic DPI scaling

The default pointer DPI ranges from `300` to `1000` in increments of `100`.
Sniping DPI ranges from `100` to `300` in increments of `100`.
Increasing or decreasing DPI stops at the configured maximum or minimum rather
than wrapping around to the other end of the range.

Use the following keycodes to change the default DPI:

-   `POINTER_DEFAULT_DPI_FORWARD`: increases the DPI; decreases when shifted;
-   `POINTER_DEFAULT_DPI_REVERSE`: decreases the DPI; increases when shifted.

There are 8 possible values for the default DPI.

Use the following keycodes to change the sniping mode DPI:

-   `POINTER_SNIPING_DPI_FORWARD`: increases the DPI; decreases when shifted;
-   `POINTER_SNIPING_DPI_REVERSE`: decreases the DPI; increases when shifted.

There are 3 possible values for the sniping mode DPI.

### Drag-scroll

Use the `DRAGSCROLL_MODE` keycode to enable drag-scroll on hold. Use the `DRAGSCROLL_TOGGLE` keycode to enable/disable drag-scroll on key press.

Vertical drag-scroll is reversed in this keymap. Run `EE_CLR` once after
flashing so the setting is copied into the pointing-device configuration.

### Sniping

Use the `SNIPING_MODE` keycode to enable sniping mode on hold. Use the `SNIPING_MODE_TOGGLE` (aliased as `SNP_TOG`) keycode to enable/disable sniping mode on key press.

Change the value of `CHARYBDIS_AUTO_SNIPING_ON_LAYER` to automatically enable sniping mode on layer change. By default, sniping mode is enabled on the pointer layer:

```c
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER
```

### Auto pointer layer

The pointer layer can be automatically enabled when moving the trackball. To enable or disable this behavior, add or remove the following define:

```c
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
```

By default, the layer is turned off 1 second after the last registered trackball movement:

```c
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
```

The trigger sensibility can also be tuned. The lower the value, the more sensible the trigger:

```c
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
```

## Layout

![Keymap layout (generated with keyboard-layout-editor.com)](https://i.imgur.com/uHEnqEN.png)
