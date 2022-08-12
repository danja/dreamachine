# dreamachine

_a flashy-light trippy thing_

Here's a [blog post](https://hyperdata.it/blog/2022/08/12/dreamachine-1/) with some background.

The plan is to make a _personal_ version of the [Dreamachine](https://en.wikipedia.org/wiki/Dreamachine), a "stroboscopic flickering light art device that produces eidetic visual stimuli".

It has sunglasses-mounted LEDs, audio output for headphones (TODO), with two rotary encoders and a tiny LCD display for control.

The device is being built around the ESP32 microcontroller module, hardware currently on a breadboard. For software development I'm using PlatformIO (on VSCode on Ubuntu).

### Status

The hardware, except for audio-related, is assembled and tested. I've a reasonable plan for functionality, see [requirements.md](https://github.com/danja/dreamachine/blob/main/design/requirements.md). I've got the skeleton of software together with basic interfaces for the LED lights, rotary encoders and display. I wasn't happy with an off-the shelf rotary encoder library so I've been rewriting that : [Esp32RotaryEncoder](https://github.com/danja/Esp32RotaryEncoder). That still needs a bit of work but is basically working, good enough to proceed.
