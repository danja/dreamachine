#include <Arduino.h>
#include <Noise.h>

//// timer bits
hw_timer_t *noiseTimer = NULL;
volatile SemaphoreHandle_t noiseTimerSemaphore;
portMUX_TYPE noiseTimerMux = portMUX_INITIALIZER_UNLOCKED;

int x = 0;

void IRAM_ATTR onNoiseTimer()
{
    portENTER_CRITICAL_ISR(&noiseTimerMux);
    //  outputNextValue();
    if (x == 0)
    {
        x = 255;
    }
    else
    {
        x = 0;
    }
    dacWrite(DAC_1, x);
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

void Noise::checkTimer()
{
    if (xSemaphoreTake(noiseTimerSemaphore, 0) == pdTRUE)
    {
        portENTER_CRITICAL(&noiseTimerMux);
        //        outputNextValue();
        portEXIT_CRITICAL(&noiseTimerMux);
    }
}
