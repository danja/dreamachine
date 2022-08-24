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
    // display.clearDisplay();
}

void TinyDisplay::init()
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

    display.display();
    delay(2000);
    display.clearDisplay();
    display.setTextColor(WHITE);
}

void TinyDisplay::refresh()
{
    Serial.print("refresh, label = ");
    Serial.println(label.c_str());
    Serial.print("refresh, value = ");
    Serial.println(value.c_str());

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println(label.c_str());
    display.setCursor(0, 20);
    display.setTextSize(4);
    display.println(value.c_str());
    display.display();
}

void TinyDisplay::drawLabel(const string newLabel)
{
    label = newLabel;
    refresh();
}

void TinyDisplay::drawValue(string newValue)
{
    value = newValue;
    refresh();
}