#include <Arduino.h>
// #include <cmath.h>
#include <LFO.h>
#include <dispatcher.hpp>

const int N_STEPS = 256;

//// timer bits
hw_timer_t *timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t stepCounter = 0;
// volatile uint32_t lastIsrAt = 0;
////////////////////
bool on = false;

void IRAM_ATTR onTimer()
{
    // Increment the counter and set the time of ISR
    portENTER_CRITICAL_ISR(&timerMux);
    stepCounter++;
    //   lastIsrAt = millis();
    portEXIT_CRITICAL_ISR(&timerMux);
    // Give a semaphore that we can check in the loop
    xSemaphoreGiveFromISR(timerSemaphore, NULL);
    // It is safe to use digitalRead/Write here if you want to toggle an output
}

LFO::LFO()
{

    // Create semaphore to inform us when the timer has fired
    timerSemaphore = xSemaphoreCreateBinary();

    // Use 1st timer of 4 (counted from zero).
    // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
    // info).
    timer = timerBegin(0, 80, true);

    // Attach onTimer function to our timer.
    timerAttachInterrupt(timer, &onTimer, true);

    // Set alarm to call onTimer function every second (value in microseconds).
    // Repeat the alarm (third parameter)
    timerAlarmWrite(timer, this->period, true);

    // Start an alarm
    timerAlarmEnable(timer);
}

void LFO::setFrequency(float freq)
{
    // Serial.begin(115200);
    this->frequency = freq;
    this->setPeriod(1000000.0 / freq);
    Serial.println(this->period);
}

void IRAM_ATTR LFO::setPeriod(int period)
{
    this->period = period / N_STEPS;
    //   portENTER_CRITICAL(&timerMux);
    timerAlarmWrite(timer, this->period, true);
    // portEXIT_CRITICAL(&timerMux);
}

void LFO::makeWaves(uint32_t step)
{
    // Serial.println(step);
    int square = 0;
    if (step > 128)
    {
        square = 255;
    }
    float x = 2 * 3.1416 * (float)step / (float)N_STEPS;
    int sine = 128 + 128.0 * sin(x);
    dispatcher.broadcast(sine);
}

void LFO::checkTimer()
{
    if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
    {
        uint32_t currentStep = 0, isrTime = 0;
        // Read the interrupt count and time
        portENTER_CRITICAL(&timerMux);
        if (stepCounter >= N_STEPS)
        {
            stepCounter = 0;
        }
        currentStep = stepCounter;
        //  isrTime = lastIsrAt;
        portEXIT_CRITICAL(&timerMux);

        makeWaves(currentStep);
    }
}

void LFO::killTimer()
{
    if (timer)
    {
        // Stop and free timer
        timerEnd(timer);
        timer = NULL;
    }
}
