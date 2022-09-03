# dreamachine

_a flashy-light trippy thing_

[Documentation Home](https://danja.github.io/projects/dreamachine/)

The plan is to make a _personal_ version of the [Dreamachine](https://en.wikipedia.org/wiki/Dreamachine), a "stroboscopic flickering light art device that produces eidetic visual stimuli".

![breadboard](https://github.com/danja/dreamachine/blob/main/images/breadboard_2022-08-12.jpeg?raw=true)

It has sunglasses-mounted LEDs, audio output for headphones (TODO), with two rotary encoders and a tiny LCD display for control. It will have audio output for headphones, providing modulated white/pink noise.

The device is being built around the ESP32 microcontroller module, hardware currently on a breadboard. For software development I'm using PlatformIO (on VSCode on Ubuntu).

I'm organising notes as I go along, the raw material is in [devlog.md](https://github.com/danja/dreamachine/blob/main/devlog.md), wiring in [wiring.md](https://github.com/danja/dreamachine/blob/main/design/wiring.md), parts list in [components.md](https://github.com/danja/dreamachine/blob/main/design/components.md).

### Status

**2022-09-03**
Hardware (mostly) done on breadboard, hard parts of the software (concurrency bits), [documentation](https://danja.github.io/projects/dreamachine/) nearly up-to-date.

Detailed status is in [devlog.md](https://github.com/danja/dreamachine/blob/main/devlog.md).
