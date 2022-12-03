
#ifndef TinyDisplay_h
#define TinyDisplay_h

#include <iostream>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include <Adafruit_SH1106.h>

using namespace std;

class TinyDisplay
{

public:
    TinyDisplay();

    void init();
    void drawLabel(const string label);
    void drawValue(const string value);

private:
    void refresh();
    Adafruit_SSD1306 display;
    // Adafruit_SH1106 display2;
    string label;
    string value;
};

#endif