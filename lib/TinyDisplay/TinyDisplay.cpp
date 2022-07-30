#include <TinyDisplay.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

TinyDisplay::TinyDisplay()
{
    // Serial.begin(9600);
    // Serial.println("TD constructor");
    display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
}

void TinyDisplay::init()
{

    // Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
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
    //  display.drawPixel(10, 10, WHITE);

    display.display();
}

void TinyDisplay::drawLabel(const String label)
{
    // display.clearDisplay();

    display.setCursor(0, 0); // Start at top-left corner

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(WHITE);
    //   display.println(F("Hello, world!"));
    display.println(label);
    display.display();
}

void TinyDisplay::drawValue(String value)
{
    display.setCursor(0, 20); // Start at top-left corner

    display.setTextSize(4); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.println(value);
    display.display();
}