
#ifndef TinyDisplay_h
#define TinyDisplay_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class TinyDisplay
{

public:
    TinyDisplay();

    void init();
    void drawLabel(const String label);
    void drawValue(const String value);

private:
    Adafruit_SSD1306 display;
};

#endif