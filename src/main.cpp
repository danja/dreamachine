#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <TinyDisplay.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

TinyDisplay tinyDisplay = TinyDisplay();

void setup()
{
    Serial.begin(115200);

    tinyDisplay.init();

    tinyDisplay.drawLabel("Starting...");
    tinyDisplay.drawValue("0%");
    delay(2000);
    tinyDisplay.drawValue("100%");
    delay(2000);
    tinyDisplay.drawLabel("Working");
}

void loop()
{
}
