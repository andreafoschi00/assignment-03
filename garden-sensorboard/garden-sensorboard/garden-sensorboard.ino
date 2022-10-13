#include <Arduino.h>

#include "Config.h"
#include "HttpService.h"
#include "WifiConnector.h"
#include "Led.h"
#include "LightSensor.h"
#include "LightSensorImpl.h"
#include "TempSensor.h"
#include "TempSensorTMP36.h"

// hardware components
TempSensor* tempSensor;
LightSensor* lightSensor;
Led* led;

// http
HttpService* httpService;
WifiConnector* wifiConnector;

enum { NORMAL,
       ALARM } state;

void setup() {
    // hardware
    Serial.begin(115200);
    tempSensor = new TempSensorTMP36(TEMP_SENSOR_PIN);
    lightSensor = new LightSensorImpl(PHOTORESISTOR_PIN);
    led = new Led(LED_PIN);

    // http
    wifiConnector = new WifiConnector(WIFI_SSID, PASSWORD);
    wifiConnector->connect();
    httpService = new HttpService();

    state = NORMAL;
}

void loop() {
    if (wifiConnector->isConnected()) {
        switch (state) {
            case NORMAL: {
                int lightIntensity = lightSensor->getLightIntensity();
                int temperatureMapped = map(tempSensor->getTemperature(), 0, 40, 1, 5);

                const char *stateSend = "auto";
                
                if(String(httpService->getState()) == "manual") {
                  stateSend = "manual";
                }
                
                // post lightIntensity, temperatureMapped, state
                int postCode = httpService->post(lightIntensity, temperatureMapped, stateSend);

                if (postCode == 200) {
                    Serial.println("ok");
                } else {
                    Serial.println(String("error: ") + postCode);
                }
                
                delay(5000);

                if (temperatureMapped == 5) {
                    // ALARM
                    state = ALARM;
                }
                led->switchOn();
                break;
            }

            case ALARM: {
                led->switchOff();
                if (httpService->getState() == "auto") {
                    state = NORMAL;
                }
                break;
            }
        }
    } else {
        Serial.println("WiFi Disconnected... Reconnect.");
        wifiConnector->connect();
    }
}
