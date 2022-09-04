```
ESP32
5v       +5v
3v3      display 3.3v

GPIO 2 (on-board LED)
GPIO 4  *** Encoder 2 SW
GPIO 13 (JTAG)
GPIO 16 *** Encoder 1 SW
GPIO 17
GPIO 18
GPIO 19
GPIO 21 *** Display SCL
GPIO 22 *** Display SCL
GPIO 23
GPIO 25
GPIO 26
GPIO 27
GPIO 32
GPIO 33
GPIO 34 (input only) *** Encoder 1 CLK
GPIO 35 (input only) *** Encoder 1 DT
GPIO 36 (input only) *** Encoder 2 CLK
GPIO 39 (input only) *** Encoder 12 DT

https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

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
