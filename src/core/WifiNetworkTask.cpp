//
// Created by mw on 30.06.19.
//

#include "WifiNetworkTask.h"
#include <Log64.h>


void WifiNetworkTask::setup() {
  WiFi.mode(WIFI_STA);
  connectToWifiNetworkIfNeeded();
}

void WifiNetworkTask::run() {
  connectToWifiNetworkIfNeeded();

  bool connectedStatus = isConnected();
  for (auto& listener: listeners)
    listener->onStatus(connectedStatus);
}

void WifiNetworkTask::connectToWifiNetworkIfNeeded() {
  if (!isConnected() && connectIsTimedout())
    connect();
}

WifiNetworkTask::WifiNetworkTask(const std::string &ssid, const std::string password, const long maxConnectMillis)
    : ssid(ssid),
      password(password), maxConnectMillis(maxConnectMillis) {}

bool WifiNetworkTask::connectIsTimedout() {
  return tsLastAttemptOrLastConnected == -1 || tsLastAttemptOrLastConnected + maxConnectMillis < millis();
}

void WifiNetworkTask::connect() {
  LOG64_SET("New attempt to connect to Wifi network");
  LOG64_NEW_LINE;
  WiFi.begin(ssid.c_str(), password.c_str());
  tsLastAttemptOrLastConnected = millis();
}
