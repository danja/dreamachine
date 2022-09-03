# Design/Functional Requirements

## Output

### Hardware

- pair of 1W white LEDs (attached inside sunglasses)
- driver for stereo headphones (speakers TBD)

### Software

- low-frequency flashing of the LEDs
- pink & white noise generation

_(adjustable, see modes below)_

## User Interface

### Hardware

- two rotary encoders (with pushswitches)
- tiny OLED display

### Software

The hardware controls/display allow the navigation of the following modes for adjusting settings:

**Light Modes**

- Brightness (overall, 0-100%)
- Frequency (1-50Hz)
- Light Phase (between left/right LEDs, 0-360°)
- Light Balance (level offset, -50...50)
- Light Wave (sine/square)

**Sound Modes**

- Volume (overall, 0-100%)
- Audio Balance (level offset between left/right, -50...50)
- Audio Phase (between left/right channel, 0-360°)
- Sound Wave (white/pink noise)

---

safety :

- always start with LEDs off when switched on
- push switch to immediately switch LEDs off
- timer controlling active period - initially say 1 min (epilepsy)
