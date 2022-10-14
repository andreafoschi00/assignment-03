#include "TempSensorTMP36.h"
#include "Arduino.h"

#define VCC ((float)3.3) // ESP use 3.3 Volt

TempSensorTMP36::TempSensorTMP36(int p) : pin(p){ }

float TempSensorTMP36::getTemperature(){
  int value = analogRead(pin);
  float valueInVolt = value / 1023.0;
  float valueInCelsius = (valueInVolt - 0.5) * 100;
  return valueInCelsius;
}
