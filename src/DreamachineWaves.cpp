#include <Arduino.h>
#include <DreamachineWaves.h>

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
    while (1)
    {
        Serial.println("Waves");
        delay(200);
    }
}
