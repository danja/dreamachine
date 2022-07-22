# dreamachine

_a flashy-light trippy thing_

I'm writing this as a brain-dump blog post. Tidy up to key bits later, once I know what I'm doing.

A few months ago, along with other fun bits, a friend sent me an ESP32 module. It's been on the shelf since, waiting for me to think of a fun project he might appreciate.
A couple of days ago, I read the article in the Guardian about [Dreamachine, the psychedelic contraption hoping to blow British minds](https://www.theguardian.com/artanddesign/2022/feb/16/dreamachine-unboxed-brion-gysin-jon-hopkins-assemble). Perfect.

I heard of this thing, back in the days when I read stuff like William Burroughs. Always wanted to make one, analog electronics at the time, but components a bit too pricey.
Lights strobing around 8Hz (or more broadly 1-40Hz) on closed eyes cause artifacts to be seen, apparently.

Ok, a communal one would be better, but gotta start somewhere, a personal version, attached to sunglasses seems easiest.
Nowadays you can buy similar things online. But components have got silly-cheap.

Here are the main components I intend to use:

![components](https://github.com/danja/dreamachine/blob/main/images/1ce49ce1-ea14-4420-8ebe-79d620e7642a.jpeg)

- cheapest sunglasses they had at the Chinese shop
- 2 x 1W LEDS
- cheapest compatible display I could find : 128x64 matrix, 2 colour, has I2C interface
- ESP32
- couple of BC109 transistors to drive the LEDs
- LM386 audio amp module (not shown)
- 2xrotary encoders with pushbutton
- 3.5mm socket for LEDs, another for headphones

Power supply to be decided - probably a PP3. I think I still have some 3.3v/5v linear regulator modules designed for breadboarding.

## Functionality

- visual :flashing lights
- brightness adjustable
- frequency control say 1-50Hz
- waveform choice - sine/square
- audio : modulated white/pink noise, level enough to power earpieces
- binocular/binaural phase choice - sync or opposing

## Design

### Hardware

Using a pair of 1W LEDs is probably massive overkill for something that's going to be close to eyes, even closed ones. But it'll make the sums easier than an array/matrix of smaller ones, and easier to build physically. No need to drive them any more than seems comfortable.

Does provide the first functional requirement. For safety's sake, it must always start with the LEDs off, turn up very gradually, be able to shut off immediately. That should be doable with a rotary encoder with built in push switch. I think maybe devote one encoder to just the brightness.

For the visuals, the ESP32 has PWM outputs that should work nicely to drive an LED through a small bipolar transistor, act as a digital-to-analog converter. As long as the pulse frequency is far above the eye's persistence of vision rate (and below what the transistor can switch). Big space, what, about 50Hz to 10MHz..? I'm thinking an order around 10kHz, the ESP32 should be comfortable there.

Even tiny signal transistors can handle relatively high currents, if they're only in saturation (very low resistance) or off (very high resistance), dissipating bugger all.
I need to breadboard a bit, see what kind of voltage/signal works best, but basically a common-emitter, with a resistor on the base to limit loading of the ESP32 and a resistor in series with the LED on the collector to limit max current.

For the audio, again use PWM to behave as a DAC, any audio freq driver amp will do, just to take the load off the ESP32. Hmm. Already rethinking a little, using a LM386 would be mono, I'd like to see if antiphase makes any difference to the psycho-effect. Maybe a couple more transistors running Class A for that (common emitter again, the phones driven from collector much like the LEDs, but in a more linear range), or somewhere I have some stereo low power Class D (digital, PWM effectively) modules. Hmm. Have to play.

### Software

Google, libraries and StackOverflow. I've used the ESP32s a bit before, hate C++, but once you get used to it, it doesn't have to be rocket science.
I'll use the PlatformIO plugin on VSCode. Is much more manageable than the Arduino IDE for anything but totally trivial stuff than the Arduino IDE. This is a relatively simple system, but still it's preferable to have it done a bit more modularly that the One Big Script that the Arduino IDE leads you towards.

Need to generate sine & square waves. Also noise for audio. The ESP32 is fast enough that I'm sure a lookup table or anything remotely fancy won't be needed.

Need to read from encoders - whatever library.

Drive display - ditto.

Assuming one encoder + switch for the brightness, another for everything else (maybe a pot for audio volume?). Make it modal on clicking the switch :

- Frequency : 33
- Phase : aligned
- Wave : sine/pulse
- Noise : white/pink

what else..?

The ESP32 is also overkill for this, an Arduino Uno or whatever would be plenty. But it does leave a lot of doors open. Instead of modulated white noise why not music over Bluetooth? (OK, using PWM DAC, that will probably sound terrible). Or a joint session with a therapy colleague over the Web? (The WiFi/Web stuff on ESP32 is pretty straightforward).

Anyhow, this is a weekend project and it's only Friday night. And I want a beer.
