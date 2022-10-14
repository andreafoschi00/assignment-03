#include "HttpService.h"
#include "Config.h"

#include <ArduinoJson.h>

// Json documents for GET/POST http actions
DynamicJsonDocument jsonPost(1024);
char msg[100];

StaticJsonDocument<200> jsonGet;

HttpService::HttpService() { }

// POST
int HttpService::post(int lightIntensity, int temperatureMapped, const char* state) {
    HTTPClient http;
    http.begin(NGROK_URL);
    http.addHeader("Content-Type", "application/json");

    // Send a json object with intensity, temperature and state
    jsonPost["intensity"] = lightIntensity;
    jsonPost["temperature"] = temperatureMapped;
    jsonPost["state"] = state;

    serializeJson(jsonPost, msg);
  
    int retCode = http.POST(msg);
    http.end();

    return retCode;
}

// GET
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
        // GET the state of the first json object in the array
        state = jsonGet[0]["state"];
    } else {
        Serial.print("Error code: ");
        Serial.println(code);
        state = "auto";
    }

    http.end();

    return state;
}
