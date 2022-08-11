#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Esp32RotaryEncoder.h>
#include <TinyDisplay.h>

#include <DreamachineUI.h>

TaskHandle_t uiHandle = NULL;

const int LED_L = 32;
const int LED_R = 33;

// PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

// GPIO ports for rotary encoders
const int ENCODER_1_CLK = 34;
const int ENCODER_1_DT = 35;
const int ENCODER_1_SW = 16;

const int ENCODER_2_CLK = 36;
const int ENCODER_2_DT = 39;
const int ENCODER_2_SW = 4;

const int ENCODER_1_STEPS = 10;
const int ENCODER_2_STEPS = 10;

Esp32RotaryEncoder encoder1 = Esp32RotaryEncoder(ENCODER_1_CLK, ENCODER_1_DT, ENCODER_1_SW);
Esp32RotaryEncoder encoder2 = Esp32RotaryEncoder(ENCODER_2_CLK, ENCODER_2_DT, ENCODER_2_SW);

// forward declarations
void IRAM_ATTR encoderEvent1();
void IRAM_ATTR buttonEvent1();
void IRAM_ATTR encoderEvent2();
void IRAM_ATTR buttonEvent2();

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

    ledcSetup(ledChannel, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(LED_L, ledChannel);
    ledcAttachPin(LED_R, ledChannel);

    encoder1.setScale(0, 100, 1, true, true);
    encoder1.setup(encoderEvent1, buttonEvent1); // pass the callback functions (leave as-is)
    encoder2.setup(encoderEvent2, buttonEvent2); // pass the callback functions (leave as-is)

    while (1) // MAIN UI LOOP
    {
        Serial.println("UI");
        delay(500);
        // increase the LED brightness
        /*
        for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
        {
            //  Serial.print(dutyCycle);
            // changing the LED brightness with PWM
            ledcWrite(ledChannel, dutyCycle);
            delay(3);
        }
        */
        ////////////////////////////
        if (encoder1.buttonClicked()) // look at a flag
        {
            Serial.println("1 click!"); // do stuff
            encoder1.resetButton();     // reset the flag
        }

        if (encoder1.valueChanged()) // look at a flag
        {
            Serial.print("1 Value :"); // do stuff
            Serial.println(encoder1.getValue());
            encoder1.resetValue(); // reset the flag
        }

        if (encoder2.buttonClicked()) // look at a flag
        {
            Serial.println("2 click!"); // do stuff
            encoder2.resetButton();     // reset the flag
        }

        if (encoder2.valueChanged()) // look at a flag
        {
            Serial.print("2 Value :"); // do stuff
            Serial.println(encoder2.getValue());
            encoder2.resetValue(); // reset the flag
        }
    }
}

void IRAM_ATTR encoderEvent1()
{
    encoder1.updateValue();
}

void IRAM_ATTR buttonEvent1()
{
    encoder1.readButton_ISR();
}

void IRAM_ATTR encoderEvent2()
{
    encoder2.updateValue();
}

void IRAM_ATTR buttonEvent2()
{
    encoder2.readButton_ISR();
}