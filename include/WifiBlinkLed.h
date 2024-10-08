//
// Created by mw on 01.07.19.
//

#ifndef TEMP_WIFI_CLIENT_WIFIBLINKLED_H
#define TEMP_WIFI_CLIENT_WIFIBLINKLED_H


#include "BlinkingLed.h"

class WifiBlinkLed {
private:
    BlinkingLed *const led;
    bool connected = false;

    static logger_t logger;
    std::function<void(bool)> onStatusListener = [this](bool _connected) {
        this->onStatus(_connected);
    };

public:
    WifiBlinkLed(BlinkingLed *aLed) : led(aLed) {}

    virtual void onStatus(bool connected);

    void applyBlinkingStatus();

    void attachToNetworkTask(WifiNetworkTask *networkTask) {
        networkTask->addStatusListener(onStatusListener);
    }
};


#endif //TEMP_WIFI_CLIENT_WIFIBLINKLED_H
