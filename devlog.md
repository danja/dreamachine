**2022-08-19**

I just wasted a load more time unsuccessfully trying to implement the State pattern.



**2022-08-15**

Hah! I was setting sine wave LFO to 100Hz, Bitscope meter was saying it was 16.8Hz. Was going around in circles until I double-checked wih Bitscope DSO - that said 100Hz!

Ok, so that's near enough for now.

The noise generator bits are the fun part, leave for now.

Get the overall prog logic in place first.

Design Patterns book suggests State. Found a reasonably clear example :

https://refactoring.guru/design-patterns/state/cpp/example

Renaming State to Mode and Context to Dreamachine.

Nooo!

I got hopelessly confused, circular dependencies etc.

The functionality I need is very simple, I reckon I'll set it up with a simple switch(){} first, refactor later if it seems necessary.

**2022-08-13**

Renamed the LightWave class to LFO. It should be more general-purpose, not tied to how it is used.

Useful examples :

https://github.com/espressif/arduino-esp32/tree/master/libraries/ESP32/examples

**2022-08-12**

To try putting something on the DreamMachineWaves core, set up a timer to flash LEDs. Works a treat, at least up to 440Hz (tested with earpiece & guitar tuner!).

Code in LightWave class, derived from https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/Timer/RepeatTimer/RepeatTimer.ino

**2022-08-11**

LATER : got the encoder a bit closer, good enough for now. Split the processes off between the 2 ESP32 cores : DreamachineUI, DreamachineWaves

I got frustrated with the rotary encoder lib so have changed it radically, now is https://github.com/danja/Esp32RotaryEncoder

TODO :

- move current readme to a blog post, create something new
- encoder start, end, nSteps
- encoder set current

- state struct
- link encoder, state, display

**2022-08-10**

The other day I did get the LEDs basically working.

The code around the rotary encoders is pretty horrible, so (like the display) am putting it in a wrapper class.

I've got that basically working, still need to add button handler, tidy up.

It _is_ possible to use the change interrupt directly, but has to happen fast or it crashes -

Guru Meditation Error: Core 1 panic'ed (Interrupt wdt timeout on CPU1)

"When an interrupt handler is called, it blocks the entire system. So it must only do minimal work and return quickly. Serial communication however is slow and causes long delays. Thus, your program is terminated by the watchdog ("wdt" is the abbreviation for the watchdog)."

Which explains why the lib exposes polling as the main access method.

But the lib examples are missing an obvious trick : use the interrupt call to set a flag. With the main loop checking flag, only updating values/display when it's changed.

Grrr. The button handling code in the lib is actually disabling the button interrupt.

Need to :

- remove ESP8266 bits (for clarity)
- remove defaults
- use seperate encoder + button interrupts (setup( , ))
- remove current button handling
- add button debouncing

**2022-08-02**

Time to look at the main function of this thing : controlling the big LEDs.

I've rigged up LEDs on sunglasses with a stereo 3.5mm jack socket.

Because the LEDs might be out of circuit at times, I'll add a dummy load of 1k or so to their transistor drivers, collector to +ve.

Now I need to find two free GPIO pins that can do PWM.

GPIO 32 PWM LED_L
GPIO 33 PWM LED_R

**2022-07-30**

rotary encoders + switches basically working - counting the wrong way, I need to look how the value scaling in the lib works.

Couple of related issues I had worth noting :

The rotary encoders I have are mounted on little PCBs with 3 resistors on their backs. I haven't bothered tracing tracks, but presumably pull-up or pull-down.

I tried using GPIO 2, which is connected to an onboard LED. Stupid idea to begin with, and in practice with a resistor connected to _something_, this stopped the program uploading.

In the encoder lib code, it has some lines like :

pinMode(this->encoderAPin, INPUT_PULLDOWN);

etc.

This seemed to conflict with the onboard resistors, I got around this by adding :

pinMode(ENCODER_1_CLK, INPUT);

etc.

After the encoder objects' creation, but before begin()

---

EARLIER

Rotary encoder time. There are quite a few libs that can manage these things, probably near-equivalent. If the encoder button can be handled here that'd be convenient. I'd prefer something interrupt-driven, polling can get messy fast. This lib appears to fit the bill : https://github.com/igorantolic/ai-esp32-rotary-encoder

So installed from PlatformIO. Now to pick GPIOs - I want ones without overloaded functionality I might need elsewhere.

I want 2 encoders (with buttons). Each needs 3 GPIOs : CLK, DT, SW

The list at https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
is a great starting point (extract below)

I may use the DACs,
GPIO25
GPIO26

I'm already using:
GPIO 22 display SCL
GPIO 21 display SDA

checking for potential later use, to connect UDA1334A I2S DAC in Chatterbox:
GPIO 25
GPIO 26
GPIO 27

These look promising :
GPIO 34 input only
GPIO 35 input only
GPIO 36 input only
GPIO 39 input only

plus (both ADC/RTC, neither of which I need)
GPIO 2
GPIO 4

Ok, so try:

Encoder1 ESP32
CLK GPIO 34
DT GPIO 35
SW GPIO 2 NO! 16

Encoder2 ESP32
CLK GPIO 36
DT GPIO 39
SW GPIO 4

Hmm, that's annoying, although this lib appears to be interrupt-driven, the examples all seem to poll.
Not a big deal - I'll go along with the examples for now. If that doesn't seem nice, I must be able to add an interrupt callback encoderChanged() somewhere...

---

**2022-07-30**

I have the display working. Next step there is to make it usable. Wrap the display lib into a class that only exposes the functionality I need through simple functions.

The UI will be modal, with the press of a button changing mode.

The display is (rather bizarrely) split into two areas - a top 1/5 or so shows yellow, the rest shows blue.

I guess a simple way of exploiting this is to use the top (yellow) line to show current mode, area below the value.

Brightness : 70%
Frequency : 33 Hz
Phase : 90°
Volume : 80%
Wave : sine
Noise : white

It's a dot matrix display so I guess it makes sense to exploit this with some kind of graphic indication as well as text. That suggests three functions :

drawLabel(labelString)
drawValue(valueString)
drawGraphic(graphicObject)

(The latter two can probably be wrapped together somehow, but that can wait until later)

rename to displayXXX()

probably need a display(labelString, valueString) ..?

https://github.com/adafruit/Adafruit_SSD1306

https://github.com/adafruit/Adafruit-GFX-Library

I noticed this, don't think it was necessary : https://rntlab.com/question/esp32-oled-ssd1306-issue/

**2022-07-29**

Had a bit of trouble writing to the ESP32, the USB connection wasn't been recognised.

ls /dev/ttyUSB\*

lsmod|grep usbserial

sudo modprobe cp210x

sudo rmmod cp210x
sudo insmod /lib/modules/5.15.0-43-generic/kernel/drivers/usb/serial/cp210x.ko

uninstall brltty

systemctl stop brltty-udev.service
sudo systemctl mask brltty-udev.service
systemctl stop brltty.service
systemctl disable brltty.service

Got this display example to work (after adding forward function definitions) :

https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/

---

I thought I'd better test the LEDs, just in case. Wound up doing some [sums](https://github.com/danja/dreamachine/blob/main/images/led-driver-sums.jpeg) and [measurements](https://github.com/danja/dreamachine/blob/main/images/led-driver-measure.jpeg)

The LEDs are rated at 1W, 3.2-3.4 V 350mA, but voltage drop was actually about 2v.

I aimed for 100mA drive from a BC109 on a 5v PSU.

With the BC109 common emitter, I found a base resistor of 680R (going to +3.3v) and a collector resistor of 10R (going through LED to +5v) gave me 95mA.

It's not exactly dazzling, but may be bright enough, is certainly good enough for now.

**2022-07-23**

The LED driving and signal generation should be straightforward enough, known territory.

This display is new to me, I reckon try to get that working first, then add rotary encoders.

Libraries :

#### Display 0.96 inch SSD1306 OLED display (GM009605)

- Adafruit_SSD1306
- Adafruit_GFX
