```
ESP32
=====
GND      Ov IN also to Display etc.
5v       +5v OUT to LED positive
3v3      3.3v OUT to Display etc.

GPIO 4  Encoder 2 SW

GPIO 12 (JTAG TDI)
GPIO 13 (JTAG TCK)
GPIO 14 (JTAG TMS)
GPIO 15 (JTAG TDO)

GPIO 16 Encoder 1 SW

GPIO 21 Display SDA
GPIO 22 Display SCL

GPIO 32 Driver for LED_L
GPIO 33 Driver for LED_R

GPIO 34 Encoder 1 CLK
GPIO 35 Encoder 1 DT

GPIO 36 Encoder 2 CLK
GPIO 39 Encoder 2 DT
```

https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

```
### Display

Pin	ESP32
---------
Vin	3.3V
GND	GND
SCL	GPIO 22
SDA	GPIO 21

### Rotary Encoders

Encoder1   ESP32
----------------
CLK        GPIO 34
DT         GPIO 35
SW         GPIO 16

Encoder2   ESP32
------------------
CLK        GPIO 36
DT         GPIO 39
SW         GPIO 4

```
