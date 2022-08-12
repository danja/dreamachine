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

#define BTN_STOP_ALARM 17

hw_timer_t *timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t isrCounter = 0;
volatile uint32_t lastIsrAt = 0;

void IRAM_ATTR onTimer() // ARDUINO_ISR_ATTR
{
    // Increment the counter and set the time of ISR
    portENTER_CRITICAL_ISR(&timerMux);
    isrCounter++;
    lastIsrAt = millis();
    portEXIT_CRITICAL_ISR(&timerMux);
    // Give a semaphore that we can check in the loop
    xSemaphoreGiveFromISR(timerSemaphore, NULL);
    // It is safe to use digitalRead/Write here if you want to toggle an output
}

/************************/
/***** WAVES THREAD *****/
/************************/
void DreamachineWaves::Waves(void *pvParameter)
{
    // Serial.begin(115200);
    // Serial.println("Waves");

    // Set BTN_STOP_ALARM to input mode
    pinMode(BTN_STOP_ALARM, INPUT);

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
    timerAlarmWrite(timer, 1000000, true);

    // Start an alarm
    timerAlarmEnable(timer);

    while (1)
    {
        //  Serial.println("Waves loop");
        // If Timer has fired
        if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
        {
            uint32_t isrCount = 0, isrTime = 0;
            // Read the interrupt count and time
            portENTER_CRITICAL(&timerMux);
            isrCount = isrCounter;
            isrTime = lastIsrAt;
            portEXIT_CRITICAL(&timerMux);
            // Print it
            Serial.print("onTimer no. ");
            Serial.print(isrCount);
            Serial.print(" at ");
            Serial.print(isrTime);
            Serial.println(" ms");
        }

        /*
                if (digitalRead(BTN_STOP_ALARM) == LOW)
                {
                    // If timer is still running
                    if (timer)
                    {
                        // Stop and free timer
                        timerEnd(timer);
                        timer = NULL;
                    }
                }
                */
    }
}
