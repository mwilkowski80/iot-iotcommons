//
// Created by mw on 30.06.19.
//

#ifndef TEMP_WIFI_CLIENT_WIFINETWORKTASK_H
#define TEMP_WIFI_CLIENT_WIFINETWORKTASK_H


#include "Task.h"
#include <ESP8266WiFi.h>
#include <Log64.h>

class WifiNetworkListener {
public:
  virtual void onStatus(bool connected);
};

class WifiNetworkTask : public Task {
private:
  const std::string ssid;
  const std::string password;
  unsigned long tsLastAttemptOrLastConnected = 0;
  const unsigned long maxConnectMillis;
  std::vector<WifiNetworkListener *> listeners;

  static logger_t logger;

  void connectToWifiNetworkIfNeeded();

  bool connectIsTimedout();

  void connect();

public:
  WifiNetworkTask(const std::string &ssid, const std::string password, const long maxConnectMillis);

  void setup() override;

  void run() override;

  void addListener(WifiNetworkListener *listener) {
    listeners.push_back(listener);
  }

  bool isConnected() const {
    return WiFi.isConnected();
  }
};


#endif //TEMP_WIFI_CLIENT_WIFINETWORKTASK_H
