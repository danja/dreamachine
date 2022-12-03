**2022-12-03**

More general OLED driver :

https://github.com/olikraus/u8g2

**2022-10-11**

https://github.com/RalphBacon/226-Better-Rotary-Encoder---no-switch-bounce

**2022-10-01**

Mode class defs in Mode.h

ESPMachine::loadModes()

updates in ESPMachine.cpp

Grr! No obvious way of doing UI to split audio/visual

**2022-09-29**

Boxed!

DECOUPLING CAPS!

220uF on

I've done a little bit more putting the thing in a box.

// 820R to the base

**2022-09-13**

I've done a bit of work preparing a case for a stripboard prototype.

I've still not sorted out the rotary controller lib.

Coincidentally I got a youtube recommendation, see : https://github.com/RalphBacon/230-Ultimate-Switch-Bounce-Eliminator

That points to a pretty thorough doc : https://github.com/RalphBacon/230-Ultimate-Switch-Bounce-Eliminator/blob/main/Jack%20Ganssle%202007%20debouncing.pdf

The guy that made the video came up with a circuit that uses a diode, cap and a couple of resistors before a 74AC14 hex schmitt :

https://github.com/RalphBacon/230-Ultimate-Switch-Bounce-Eliminator/blob/main/images/Schematic.jpg

There's also a doc linked about debouncing what appears to be the same encoder that I'm using, KY-040 :

https://www.best-microcontroller-projects.com/rotary-encoder.html

This would be very useful if I was building lib from scratch, which I may do...

That also has debounce just using a series 10k then a 10n cap to ground.

---

I also posted to r/ESP32 asking about mocking something like an encoder.

https://www.reddit.com/r/esp32/comments/xbokqu/mock_objects_to_emulate_hardware/

Several responses, mostly saying don't... A couple suggested making a hardware emulator (Arduino or whatever). A couple of suggestions that might be worth looking into :

ESP32 event loops - appears to be like the Dispatcher/Observer thing I'm using elsewhere. Is in ESP-IDF, not sure if it's supported in the Arduino framework :

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/esp_event.html

MQTT : use messaging from a remote machine (via WiFi). I should look at this for more general application...

https://learn.sparkfun.com/tutorials/introduction-to-mqtt/all

**2022-09-04**

Wondering about the audio out. According to this : https://esp32.com/viewtopic.php?t=2331
the max current for a GPIO pins is 12mA. It can go up to 3.3v-ish. Discounting everything else, that would suggests a series resistor of
275R, giving a power of 40mW. Which _might_ be enough to drive earpieces...

Trying with 270R in series with a 22u capacitor.

It's not loud, but is certainly audible, and in the interests of simplicity, yeah, that'll do.

**2022-09-01**

Yay! I got the pink noise gen bit working, modulated from LFO.

Decided it was a good time to pause, do some docs, see what was needed to tidy things up.

Replaced refs to 'Dreamachine*' to 'ESPMachine*', with generalising in mind.

The SSD1306 display bits got messed up, so replaced those, redid splash screen. (There must be a way of doing it without hacking into the driver source, but I can't be bothered looking right now).

**2022-08-30**

I got a fair bit further, but along the way did a git revert, wiped the notes...

DAC GPIO are 25, 26

**2022-08-26**

The queue between processes on Core 0 and Core 1 was almost working, but :

CORRUPT HEAP: Bad head

First probably was that I was setting the queue item size from an uninitialized struct (empty box!).

Fiddled around a bit elsewhere.

The labels bizarrely kept resetting to the initialized default. I couldn't see how to check these in the debugger, but then I realised that they don't need to be passed with the message!
Much more stable now.

Ah...but I do still need to pass a ref. to the current mode...

I changed the splash screen :

- copied .pio/lib/Adafruit SSD1306 to /lib/
- removed ref in /platformio.ini
- made 128x64 .bmp in Gimp
- converted with https://javl.github.io/image2cpp/
- backed up splash.h
- pasted in my values

**2022-08-25**

This thing is so concurrency-heavy!

So now, when the Mode is changed in Dreamachine.cpp, on Core 0, I need it to pass whatever values have changed over to DreamachineWaves on Core 1.

For a similar job, in LFO, it was textbook semaphore-based so I pretty much copy-and-pasted the relevant code.

Comms between cores is central to the whole application(s), so I really need a clear idea of what's going on.

A possibility would be to use RTOS Task Notifications, eg. with

https://www.freertos.org/RTOS_Task_Notification_As_Mailbox.html

But with this :

- Only 32-bit values can be sent
- The value is saved as the receiving task's notification value, and there can only be one notification value at any one time

These are faster, and I could probably squeeze what's needed for Dreamachine into this approach, but I think it makes more sense to do it in a more general purpose way using
FreeRTOS Queues.

https://www.freertos.org/Embedded-RTOS-Queues.html

So over to:

https://www.freertos.org/Documentation/RTOS_book.html
Tutorial, Chapter 4, Queue Management

- bleah, not clear

RTOS Reference Manual, P.163

https://techtutorialsx.com/2017/08/20/esp32-arduino-freertos-queues/

**2022-08-24**

I got past my annoying problem this morning. The encoder can now update the display.

Next problem is getting it to update eg. the LED frequency.

Does get confusing fast, the different scopes, what has to be static.

**2022-08-23**

I realised an easy (but still quite clean) way to handle the different application/UI modes, 'Brightness', 'Frequency' etc, was to implement them as (an array of) objects.

But last night, coding it up, ran into trouble. So I cut the code back to something really simple, there's still a disconnect somewhere. Just now I had a look, still couldn't see the problem.

Then I remembered I'd bought an ESP Prog JTAG board when I started working on Chatterbox. Could not get it to work then.

I just plugged it into Dreamachine - It Just Worked - and now I have proper debugging!!!!

https://medium.com/@manuel.bl/low-cost-esp32-in-circuit-debugging-dbbee39e508b

```
TDI (Test Data In)
TDO (Test Data Out)
TCK (Test Clock)
TMS (Test Mode Select)
TRST (Test Reset) optional.
On the ESP32, the JTAG pins are GPIO pins at the same time. So during debugging, you cannot use them. They are:

GPIO12 — TDI
GPIO15 — TDO
GPIO13 — TCK
GPIO14 — TMS
The reset pin (TRST) is not fully supported by OpenOCD. Fortunately, it’s optional.
```

https://medium.com/@manuel.bl/low-cost-esp32-in-circuit-debugging-dbbee39e508b

I'm too tired to do any more tonight, but this should be a real timesaver. Proper magic!!!

**2022-08-21**

To try and sort out wonky organisation decided some visualisation would be useful.

Installed :

- doxygen
- doxygen-gui (runs as doxywizard) : generates config, runs
- mintlify doc writer (vscode extension) : highlight source, it generates comments

I went around and around in circles again - literally.

Getting the right bits static and the right pointer reference, hugely confusing.

But now the encoder is talking to the display via a callback to Dreamachine.cpp. Phew!!!

**2022-08-20**

It took me a long time, but I've now got an EncoderReader (wrapping both encoders) dispatching events.
But the high-level organisation is now a bit wonky :)

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
