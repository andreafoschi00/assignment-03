#ifndef __SERVO_IMPL__
#define __SERVO_IMPL__

#include <arduino.h>
#include "ServoMotor.h"
#include "ServoTimer2.h"

class ServoImpl: public ServoMotor {
  public:
    ServoImpl(int pin);

    void on();
    void setAngle(int angle);
    void off();

  private:
    int pin;
    ServoTimer2 motor;
};

#endif
