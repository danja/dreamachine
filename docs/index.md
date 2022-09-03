![logo](https://danja.github.io/projects/dreamachine/html/logo.png)

# Dreamachine

_a flashy-light trippy thing_

The plan is to make a _personal_ version of the [Dreamachine](https://en.wikipedia.org/wiki/Dreamachine), a "stroboscopic flickering light art device that produces eidetic visual stimuli".

![breadboard](https://github.com/danja/dreamachine/blob/main/images/breadboard_2022-08-12.jpeg?raw=true)

## Code

- [GitHub Repository](https://github.com/danja/dreamachine)
- [Doxygen code docs](https://danja.github.io/projects/dreamachine/html/index.html)

## Design Docs

- [Requirements](https://danja.github.io/projects/dreamachine/design/requirements.html) - _nearest thing to a_ design doc
- [Components](https://danja.github.io/projects/dreamachine/design/components.html) - _nearest thing to a_ BOM
- [Wiring](https://danja.github.io/projects/dreamachine/design/wiring.html) - _nearest thing to a_ schematic

## Blog Posts

- [Dreamachine #1 : Background](https://hyperdata.it/blog/2022/08/12/dreamachine-1/)
- [Dreamachine #2 : Pink Noise](https://hyperdata.it/blog/2022/08/31/dreamachine-2-pink-noise/)

## Videos

- [Dreamachine latest](https://www.youtube.com/shorts/KWcSSeeBIWw) (very short demo, 2022-09-01)

## See Also

- [Dreamachine](https://en.wikipedia.org/wiki/Dreamachine) on Wikipedia
- [dreamachine.world](https://dreamachine.world/) - Unboxed (Festival of Brexit) Show
- [Dreamachine, the psychedelic contraption hoping to blow British minds](https://www.theguardian.com/artanddesign/2022/feb/16/dreamachine-unboxed-brion-gysin-jon-hopkins-assemble) - Guardian review of ^^^

### Previous Status

**2022-08-12** The hardware, except for audio-related, is assembled and tested. I've a reasonable plan for functionality, see [requirements.md](https://github.com/danja/dreamachine/blob/main/design/requirements.md). I've got the skeleton of software together with basic interfaces for the LED lights, rotary encoders and display. I wasn't happy with an off-the shelf rotary encoder library so I've been rewriting that : [Esp32RotaryEncoder](https://github.com/danja/Esp32RotaryEncoder). That still needs a bit of work but is basically working, good enough to proceed.

Detailed status is in [devlog.md](https://github.com/danja/dreamachine/blob/main/devlog.md).
