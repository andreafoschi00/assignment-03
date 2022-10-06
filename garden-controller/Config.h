#ifndef __CONFIG__
#define __CONFIG__

// Pins
#define PIN_LED1 3
#define PIN_LED2 4
#define PIN_LED3 5
#define PIN_LED4 6

#define PIN_SERVO 9

#define PIN_BT_RDX 12
#define PIN_BT_TDX 13

#include <Arduino.h>

// Irrigation constants
#define IRRIGATION_TIME 10000 // --> Y seconds on the presentation file
#define SERVO_TICK 5
#define SERVO_SLEEP 10000 // --> X (minutes to seconds) on the presentation file

#endif
