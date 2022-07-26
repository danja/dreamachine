#include <Arduino.h>
#include <ESPMachineWaves.h>
// #include <ESPMachine.h>
#include <Mode.h>
#include <LFO.h>
#include <LedDriver.h>
#include <Q.h>
#include <Noise.h>

// TaskHandle_t wavesHandle = NULL;

ESPMachineWaves::ESPMachineWaves()
{
    /*
    xTaskCreatePinnedToCore(
        Waves,
        "ESPMachineWaves",
        4096, // was 2048, 4096
        NULL,
        2,            // 1 | portPRIVILEGE_BIT,
        &wavesHandle, // was &AudioTask,
        1);
        */
}

/************************/
/***** WAVES THREAD *****/
/************************/
void ESPMachineWaves::Waves(void *pvParameter)
{
    //  Serial.begin(115200);
    // Serial.println("Waves");
    delay(500);

    LFO lightwaveLFO;
    LedDriver ledDriver;

    lightwaveLFO.setFrequency(4);
    // Serial.println("Waves B");
    ledDriver.registerCallback(lightwaveLFO.dispatcher);

    Noise noise;

    noise.registerCallback(lightwaveLFO.dispatcher);

    while (1)
    {
        //   delay(1); // need to release
        // noise.outputNextValue();
        //  delayMicroseconds(10);
        noise.checkTimer();
        lightwaveLFO.checkTimer();

        ModeMessage modeMessage = ModeMessage();
        int previousIndex = modeMessage.index;
        long previousValue = modeMessage.value;

        xQueueReceive(intercoreQueue, &modeMessage, QUEUE_RECEIVE_DELAY); // portMAX_DELAY
        // Serial.println("-------------");
        // Serial.println(modeMessage.index);
        // Serial.println(modeMessage.value);

        if (previousIndex != modeMessage.index || previousValue != modeMessage.value)
        {
            //   Serial.println("-------------");
            // Serial.println(modeMessage.index);
            // Serial.println(modeMessage.value);
            switch (modeMessage.index)
            {
            case modeSelect::BRIGHTNESS:
                //   Serial.println("Brightness");

                ledDriver.setBrightness(((float)modeMessage.value) / 100.0); // SCALE
                break;

            case modeSelect::FREQUENCY:
                lightwaveLFO.setFrequency(modeMessage.value);
                break;
            case modeSelect::LIGHT_BALANCE:
                break;
            case modeSelect::LIGHT_PHASE:
                break;

            case modeSelect::LIGHT_WAVE:
                if (modeMessage.value > 0)
                {
                    //  Serial.println("SQUARE");
                    ledDriver.setWaveform(Waveform::SQUARE);
                }
                else
                {
                    ledDriver.setWaveform(Waveform::SINE);
                }
                break;

            case modeSelect::SOUND_WAVE:
                break;
            case modeSelect::AUDIO_BALANCE:
                break;
            case modeSelect::AUDIO_PHASE:
                break;
            case modeSelect::VOLUME:
                break;
            default:
                return;
            }
        }
    }
}
