#ifndef __HTTP_SERVICE__
#define __HTTP_SERVICE__

#include "HTTPClient.h"
#include "WifiConnector.h"

// This class manage the GET and POST actions of HTTP using HTTPClient library

class HttpService {
   public:
    HttpService();
    int post(int lightIntensity, int temperatureMapped, const char* state);
    const char* getState();

   private:
    HTTPClient http;
};

#endif
