**2022-07-29**

I thought I'd better test the LEDs, just in case. Wound up doing some [sums]() and [measurements]()

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
