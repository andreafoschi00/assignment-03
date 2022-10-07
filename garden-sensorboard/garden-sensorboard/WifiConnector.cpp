#include "WifiConnector.h"

#include <WiFi.h>

WifiConnector::WifiConnector(const char* ssid, const char* password) {
    this->ssid = ssid;
    this->password = password;
}

void WifiConnector::connect() {
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}

bool WifiConnector::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WifiConnector::disconnect() {
    WiFi.disconnect();
}
