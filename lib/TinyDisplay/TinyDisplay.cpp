#include <TinyDisplay.h>

TinyDisplay::TinyDisplay()
{
}

void TinyDisplay::init()
{

    display.begin();
    display.display();
    delay(1000); //

    display.clearDisplay();
    display.setDrawColor(1);
    // display.setTextColor(WHITE);
    display.firstPage();
    do
    {
        display.setFont(u8g2_font_ncenB14_tr);
        display.drawStr(0, 20, "Hello World!");
    } while (display.nextPage());
}

void TinyDisplay::refresh()
{

    /*
    Serial.print("refresh, label = ");
    Serial.println(label.c_str());
    Serial.print("refresh, value = ");
    Serial.println(value.c_str());
*/
    display.clearDisplay();
    display.setFont(u8g2_font_ncenB14_tr);
    display.setCursor(0, 0);
    display.drawStr(0, 0, label.c_str());
    // display.println(label.c_str());
    display.setCursor(0, 20);
    //  display.setTextSize(4);
    // display.println(value.c_str());
    display.drawStr(0, 20, value.c_str());
    // display.display();
    display.nextPage();
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