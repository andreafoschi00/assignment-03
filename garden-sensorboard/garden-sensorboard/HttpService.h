#ifndef __HTTP_SERVICE__
#define __HTTP_SERVICE__

#include <HTTPClient.h>
#include "WifiConnector.h"

class HttpService {
   public:
    HttpService();
    int post(int lightIntensity, int temperatureMapped, const char* state);
    const char* getState();

   private:
    HTTPClient http;
};

#endif
