#include "TempSensorTMP36.h"
#include "Arduino.h"

#define VCC ((float)5)

TempSensorTMP36::TempSensorTMP36(int p) : pin(p){
}

float TempSensorTMP36::getTemperature(){
  int value = analogRead(pin);
  float valueInVolt = value * VCC / 1024.0;
  float valueInCelsius = (valueInVolt - 0.5) * 100;
  return valueInCelsius;
}
