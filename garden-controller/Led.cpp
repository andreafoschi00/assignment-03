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
    analogWrite(pin, int(map(value, 0, 4, 51, 255)));
  }
}
