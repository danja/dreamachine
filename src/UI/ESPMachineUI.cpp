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

//  (float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues)

void ESPMachineUI::configureEncoder1(float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues)
{
    encodersReader.configure1(startValue, minValue, maxValue, stepSize, invert, circleValues);
}

void ESPMachineUI::configureEncoder2(float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues)
{
    encodersReader.configure2(startValue, minValue, maxValue, stepSize, invert, circleValues);
}

void ESPMachineUI::updateDisplay(string label, string value)
{
    tinyDisplay.drawLabel(label);
    tinyDisplay.drawValue(value);
}
