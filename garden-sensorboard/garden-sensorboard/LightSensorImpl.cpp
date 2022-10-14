#include "LightSensorImpl.h"

#include "Arduino.h"

LightSensorImpl::LightSensorImpl(int pin) {
    this->pin = pin;
}

int LightSensorImpl::getLightIntensity() {
    int value = analogRead(pin);
    return map(value, 0, 4095, 0, 7);  // range: 0..7, photoresistor accepts values 0...4095
}
