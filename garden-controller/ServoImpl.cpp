#include "Arduino.h"
#include "ServoImpl.h"

ServoImpl::ServoImpl(int pin) {
  this->pin = pin;
}

void ServoImpl::on(){
  motor.attach(pin);
}

void ServoImpl::setAngle(int angle) {
  if(angle > 180) {
    angle = 180;
  } else if (angle < 0) {
    angle = 0;
  }

  float coeff = (2400.0 - 544.0) / 180;
  motor.write(544 + angle * coeff);
}

void ServoImpl::off(){
  motor.detach();
}
