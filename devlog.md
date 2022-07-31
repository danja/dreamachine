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
