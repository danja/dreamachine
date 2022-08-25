#include <Arduino.h>
#include <DreamachineWaves.h>
// #include <Dreamachine.h>
#include <Mode.h>
#include <LFO.h>
#include <LedDriver.h>
#include <Q.h>

TaskHandle_t wavesHandle = NULL;

// QueueHandle_t queue; // Q

DreamachineWaves::DreamachineWaves()
{
    xTaskCreatePinnedToCore(
        Waves,
        "DreamachineWaves",
        4096, // was 2048, 4096
        NULL,
        2,            // 1 | portPRIVILEGE_BIT,
        &wavesHandle, // was &AudioTask,
        1);
}

/*
void DreamachineWaves::setDreamachine(Dreamachine dreamachine)
{
    this->dreamachine = dreamachine;
}
*/

/************************/
/***** WAVES THREAD *****/
/************************/
void DreamachineWaves::Waves(void *pvParameter)
{
    //  Serial.begin(115200);
    // Serial.println("Waves");

    LFO lightwave;
    LedDriver ledDriver;

    lightwave.setFrequency(4);
    // Serial.println("Waves B");
    ledDriver.registerCallback(lightwave.dispatcher);

    while (1)
    {
        delay(10); // need to release
                   // Serial.println("Waves");
        lightwave.checkTimer();

        ModeMessage modeMessage = ModeMessage();
        long x = modeMessage.value;
        xQueueReceive(queue, &modeMessage, 0); // portMAX_DELAY
        if (x != modeMessage.value)
        {
            // Serial.println(modeMessage.value);
            lightwave.setFrequency(modeMessage.value);
        }
    }
}

void DreamachineWaves::setLightFrequency(int frequency)
{
    //    lightwave.setFrequency(frequency);
}
