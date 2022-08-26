#ifndef _QQQQ_H
#define _QQQQ_H

#include <Arduino.h>

extern QueueHandle_t intercoreQueue; // Q

// used in Dreamachine.cpp
const int QUEUE_ITEM_SIZE = sizeof(AModeMessage); // Q
const int QUEUE_LENGTH = 5;                       // Q
const int QUEUE_SEND_DELAY = 100;                 // Q // portMAX_DELAY

// used in DreamachineUI.cpp
const int QUEUE_RECEIVE_DELAY = 1; // Q portMAX_DELAY

#endif