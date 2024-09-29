//
// Created by mw on 27.09.24.
//

#include "../include/HomeAssistant.h"
#include <ArduinoJson.h>

int HomeAssistant::setState(const String &entityId, const String &state) {
    HTTPClient http;
    WiFiClient wifi_client;

    auto url = baseUrl + "/api/states/" + entityId;
    http.begin(wifi_client, url);
    addHeaders(http);

    String payload;
    JsonDocument jsonObject;
    jsonObject["state"] = state.c_str();
    serializeJson(jsonObject, payload);

    logger("Sending POST to " + url + ", payload: " + payload);
    auto result = http.POST(payload);
    logger("POST error code: " + String(result));
    return result;
}

int HomeAssistant::getState(const String &entityId, String *output) {
    HTTPClient http;
    WiFiClient wifi_client;

    auto url = baseUrl + "/api/states/" + entityId;
    http.begin(wifi_client, url);
    addHeaders(http);

    logger("Invoking GET at " + url);
    auto errorCode = http.GET();
    logger("GET error code: " + String(errorCode));
    if (HomeAssistant::isSuccess(errorCode)) {
        *output = http.getString();
    }
    return errorCode;
}

int HomeAssistant::setInputNumber(const String &entityId, const float value) {
    HTTPClient http;
    WiFiClient wifi_client;

    auto url = baseUrl + "/api/services/input_number/set_value";
    http.begin(wifi_client, url);
    addHeaders(http);

    JsonDocument doc;
    doc["entity_id"] = entityId;
    doc["value"] = value;
    String payload;
    serializeJson(doc, payload);

    logger("Invoking POST at " + url);
    auto errorCode = http.POST(payload);
    logger("POST error code: " + String(errorCode));
    return errorCode;
}
