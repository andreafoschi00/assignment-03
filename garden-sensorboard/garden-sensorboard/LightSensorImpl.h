#include "LightSensor.h"

// Photoresistor --> reads intensity

class LightSensorImpl : public LightSensor {
   public:
    LightSensorImpl(int pin);
    int getLightIntensity();

   private:
    int pin;
};
