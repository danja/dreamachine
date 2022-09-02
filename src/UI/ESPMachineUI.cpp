#include <Arduino.h>

#include <EncoderReader.h>
#include <TinyDisplay.h>

#include <ESPMachineUI.h>

// TaskHandle_t uiHandle = NULL;

ESPMachineUI::ESPMachineUI()
{
}

/*
ESPMachineUI::ESPMachineUI()
{
    xTaskCreatePinnedToCore(
        UI,
        "ESPMachineUI",
        4096, // stack size, was 4096, 64000 // high 97004
        NULL,
        2, // priority
        &uiHandle,
        0); // core
}
*/
TinyDisplay tinyDisplay = TinyDisplay();

EncoderReader encoderReader;

void ESPMachineUI::attachEncoder(ESPMachine dreamachine) // should probably extract interface
{
    dreamachine.registerCallback(encoderReader.buttonDispatcher);
    dreamachine.registerCallback(encoderReader.encoderDispatcher);
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

        encoderReader.operate();
    }
}

void ESPMachineUI::updateDisplay(string label, string value)
{
    tinyDisplay.drawLabel(label);
    tinyDisplay.drawValue(value);
}
