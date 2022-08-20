#include <Arduino.h>

#include <EncoderReader.h>
#include <TinyDisplay.h>

#include <DreamachineUI.h>

TaskHandle_t uiHandle = NULL;

DreamachineUI::DreamachineUI()
{
    xTaskCreatePinnedToCore(
        UI,
        "DreamachineUI",
        4096, // stack size, was 4096, 64000 // high 97004
        NULL,
        2, // priority
        &uiHandle,
        0); // core
}

TinyDisplay tinyDisplay = TinyDisplay();

EncoderReader encoderReader;

/*********************/
/***** UI THREAD *****/
/*********************/
void DreamachineUI::UI(void *pvParameter)
{
    tinyDisplay.init();

    tinyDisplay.drawLabel("Starting...");
    tinyDisplay.drawValue("0%");
    // delay(500);
    tinyDisplay.drawValue("100%");
    // delay(500);
    tinyDisplay.drawLabel("Working");

    while (1) // MAIN UI LOOP
    {
        Serial.println("UI");
        delay(500);
        // increase the LED brightness
        encoderReader.operate();
    }
}
