#include <Arduino.h>

#include <EncodersReader.h>
#include <TinyDisplay.h>

#include <ESPMachineUI.h>

ESPMachineUI::ESPMachineUI()
{
}

TinyDisplay tinyDisplay = TinyDisplay();

EncodersReader encodersReader;

void ESPMachineUI::attachEncoder(ESPMachine dreamachine) // should probably extract interface
{
    encodersReader.init();
    dreamachine.registerCallback(encodersReader.buttonDispatcher);
    dreamachine.registerCallback(encodersReader.encoderDispatcher);
}

/*********************/
/***** UI THREAD *****/
/*********************/
void ESPMachineUI::UI(void *pvParameter)
{
    tinyDisplay.init();
    delay(100);

    while (1) // MAIN UI LOOP
    {
        //     Serial.println("UI");
        delay(10);
        encodersReader.operate();
    }
}

// void EncodersReader::setScale1(long minValue, long maxValue, long steps, boolean invert, bool circleValues)

void ESPMachineUI::initEncoder1(long currentValue, long minValue, long maxValue, long steps, boolean invert, bool circleValues)
{
    encodersReader.setScale1(minValue, maxValue, steps, invert, circleValues);
}

void ESPMachineUI::initEncoder2(long currentValue, long minValue, long maxValue, long steps, boolean invert, bool circleValues)
{
    encodersReader.setScale2(minValue, maxValue, steps, invert, circleValues);
}

void ESPMachineUI::updateDisplay(string label, string value)
{
    tinyDisplay.drawLabel(label);
    tinyDisplay.drawValue(value);
}
