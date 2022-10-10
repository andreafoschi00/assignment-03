#include "HttpService.h"

#include <ArduinoJson.h>

#include "Config.h"
#include "HTTPClient.h"

DynamicJsonDocument jsonPost(1024);
char msg[100];

DynamicJsonDocument jsonGet(1024);

HttpService::HttpService() {
}

int HttpService::post(int lightIntensity, int temperatureMapped, const char* state) {
    HTTPClient http;
    http.begin(NGROK_URL);
    http.addHeader("Content-Type", "application/json");


    jsonPost["intensity"] = lightIntensity;
    jsonPost["temperature"] = temperatureMapped;
    jsonPost["state"] = state;

    serializeJson(jsonPost, msg);
  
    Serial.println(lightIntensity);
    Serial.println(temperatureMapped);
    Serial.println(state);

    int retCode = http.POST(msg);
    http.end();

    return retCode;
}

const char* HttpService::getState() {
    HTTPClient http;
    http.begin(NGROK_URL);
    const char* state;

    int code = http.GET();
    if (code > 0) {
        char payload[100];
        String jsonString = http.getString();
        jsonString.toCharArray(payload, jsonString.length() + 1);

        deserializeJson(jsonGet, payload);
        state = jsonGet["state"];
    } else {
        Serial.print("Error code: ");
        Serial.println(code);
        state = "auto";
    }

    http.end();

    return state;
}
