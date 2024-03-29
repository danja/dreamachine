
#ifndef TinyDisplay_h
#define TinyDisplay_h

#include <iostream>

#include <U8g2lib.h>
#include <Wire.h>

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

    U8G2_SH1106_128X64_NONAME_1_HW_I2C display = U8G2_SH1106_128X64_NONAME_1_HW_I2C(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

    string label;
    string value;
};

#endif