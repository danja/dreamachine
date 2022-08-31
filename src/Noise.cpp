#include <Arduino.h>
#include <Noise.h>
#include <PinkNoise.h>

//// timer bits
hw_timer_t *noiseTimer = NULL;
volatile SemaphoreHandle_t noiseTimerSemaphore;
portMUX_TYPE noiseTimerMux = portMUX_INITIALIZER_UNLOCKED;

int x = 0;

PinkNoise pinkNoise;

void IRAM_ATTR onNoiseTimer()
{
    portENTER_CRITICAL_ISR(&noiseTimerMux);
    //  outputNextValue();

    //  dacWrite(DAC_1, random(256));
    //   dacWrite(DAC_1, pinkNoise.tick() * 256);

    portEXIT_CRITICAL_ISR(&noiseTimerMux);

    xSemaphoreGiveFromISR(noiseTimerSemaphore, NULL);
    // It is safe to use digitalRead/Write here if you want to toggle an output
}

Noise::Noise()
{
    // Create semaphore to inform us when the timer has fired
    noiseTimerSemaphore = xSemaphoreCreateBinary();

    // Use 2st timer of 4 (counted from zero).
    // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
    // info).
    noiseTimer = timerBegin(NOISE_TIMER, NOISE_PRESCALE, true);

    // Attach onTimer function to our timer.
    timerAttachInterrupt(noiseTimer, &onNoiseTimer, true);

    // Set alarm to call onTimer function every second (value in microseconds).
    // Repeat the alarm (third parameter)
    timerAlarmWrite(noiseTimer, NOISE_PERIOD, true);

    // Start an alarm
    timerAlarmEnable(noiseTimer);
}

long mino = 0;
long maxo = 0;

void Noise::checkTimer()
{
    if (xSemaphoreTake(noiseTimerSemaphore, 0) == pdTRUE)
    {
        portENTER_CRITICAL(&noiseTimerMux);
        //        outputNextValue();
        dacWrite(DAC_1, random(256));

        int out = pinkNoise.tick() + 182;
        dacWrite(DAC_2, out);
        //   Serial.println(out);
        /*
        if (out > maxo)
            maxo = out;
        if (out < mino)
            mino = out;
        Serial.println(mino);
        Serial.println(maxo);
        */
        portEXIT_CRITICAL(&noiseTimerMux);
    }
}
