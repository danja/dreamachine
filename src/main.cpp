#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

using namespace std;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void drawLabel(String label);
void drawValue(String value);

void setup()
{
    Serial.begin(115200);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();

    // Draw a single pixel in white
    display.drawPixel(10, 10, WHITE);

    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(2000); // Pause for 2 seconds

    display.clearDisplay();
    String label = "Love You";
    drawLabel(label);
    drawValue("100%");
}

void loop()
{
}

void drawLabel(String label)
{
    // display.clearDisplay();

    display.setCursor(0, 0); // Start at top-left corner

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(WHITE);
    //   display.println(F("Hello, world!"));
    display.println(label);
    display.display();
}

void drawValue(String value)
{
    //  display.clearDisplay();

    display.setCursor(0, 20); // Start at top-left corner

    display.setTextSize(4); // Draw 2X-scale text
    display.setTextColor(WHITE);
    //   display.println(F("Hello, world!"));
    display.println(value);
    display.display();
}
