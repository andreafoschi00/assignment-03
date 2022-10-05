#ifndef __CONFIG__
#define __CONFIG__

#define PIN_LED1 3
#define PIN_LED2 4
#define PIN_LED3 5
#define PIN_LED4 6

#define PIN_SERVO 9

#define PIN_BT_RDX 12
#define PIN_BT_TDX 13

#include Arduino.h

#define AUTO_MODE 1
#define MANUAL_MODE 2
#define ALARM_MODE 3

extern int status;

#endif
