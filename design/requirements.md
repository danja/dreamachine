# Functional Requirements

Easiest to describe in terms of the user interface.

safety :

- always start with LEDs off when switched on
- push switch to immediately switch LEDs off
- timer controlling active period - initially say 1 min (epilepsy)

User Interface

Assuming one encoder + switch for the brightness, another for everything else (maybe a pot for audio volume?). Make it modal on clicking the switch :

Brightness : 0-100%
Light Balance : L% : R%
Frequency : 1-50 Hz
Wave : sine/square
Light Phase : 0-359°

Volume : 0-100%
Audio Balance : L% : R%
Noise : white/pink
Audio Phase : 0-359°
