#ifndef __WIFI_CONNECTOR__
#define __WIFI_CONNECTOR__

#include "Arduino.h"

class WifiConnector {
   public:
    WifiConnector(const char* ssid, const char* password);
    void connect();
    bool isConnected();
    void disconnect();

   private:
    const char* ssid;
    const char* password;
};

#endif
