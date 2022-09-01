#include <Arduino.h>

#include <EncoderReader.h>
#include <TinyDisplay.h>

#include <ESPMachineUI.h>

TaskHandle_t uiHandle = NULL;

/**
 * `xTaskCreatePinnedToCore(UI, "ESPMachineUI", 4096, NULL, 2, &uiHandle, 0);`
 *
 * The function `xTaskCreatePinnedToCore` creates a task (a thread) and pins it to a core. The first
 * argument is the name of the function that will be run as a task. The second argument is the name of
 * the task. The third argument is the stack size. The fourth argument is a pointer to the function's
 * arguments. The fifth argument is the priority of the task. The sixth argument is a pointer to the
 * task handle. The seventh argument is the core to pin the task to
 */
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
    // delay(500);
    // tinyDisplay.drawLabel("Starting...");
    /*
        tinyDisplay.drawLabel("Starting...");
        tinyDisplay.drawValue("0%");
        tinyDisplay.drawValue("100%");
        tinyDisplay.drawLabel("Working");
    */
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