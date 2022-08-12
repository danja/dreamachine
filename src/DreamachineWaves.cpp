#include <Arduino.h>
#include <DreamachineWaves.h>
#include <LightWave.h>

TaskHandle_t wavesHandle = NULL;

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

/************************/
/***** WAVES THREAD *****/
/************************/
void DreamachineWaves::Waves(void *pvParameter)
{
    // Serial.begin(115200);
    // Serial.println("Waves");
    LightWave lightwave;

    while (1)
    {
        lightwave.checkTimer();
        //  Serial.println("Waves loop");
        // If Timer has fired
    }
}
