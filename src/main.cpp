#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <TinyDisplay.h>

// using namespace std;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

TinyDisplay tinyDisplay = TinyDisplay();

// void drawLabel(String label);
// void drawValue(String value);

void setup()
{
    Serial.begin(9600);

    tinyDisplay.init();

    tinyDisplay.drawLabel("Working");
    tinyDisplay.drawValue("100%");
}

void loop()
{
}
