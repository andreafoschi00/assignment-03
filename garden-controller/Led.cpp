#include "Arduino.h"
#include "Led.h"

// Used to check if LED 3 and 4 are connected on PWN pins
int pwmPins[] = {3,5,6,9,10,11};

Led::Led(int pin){
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Led::turnOn(){
  digitalWrite(pin, HIGH);
}

void Led::turnOff(){
  digitalWrite(pin, LOW);
}

bool Led::isActive(){
  return digitalRead(pin);
}

void Led::turnOnWithValue(int value) {
  bool hasPWM = false;
  for(int actual_pin: pwmPins) {
    if(pin == actual_pin) {
      hasPWM = true;
      break;
    }
  }

  if(!hasPWM) {
     String msgError = "Invalid connection: PWM is not supported on pin: " + pin;
     Serial.println(msgError);
  } else {
    switch(value) {
      case 0:
        analogWrite(pin, 255);
      break;
      case 1:
        analogWrite(pin, 204);
      break;
      case 2:
        analogWrite(pin, 153);
      break;
      case 3:
        analogWrite(pin, 102);
      break;
      case 4:
        analogWrite(pin, 51);
      break;
      default:
        analogWrite(pin, 0);
      break;
    }
  }
}
