//
// Created by mw on 07.09.24.
//

#ifndef IOT_IOTCOMMONS_MULTIPLEERRORLED_H
#define IOT_IOTCOMMONS_MULTIPLEERRORLED_H


#include "Task.h"
#include "BlinkingLed.h"

template<int N>
class MultipleErrorLed : public Task {
private:
    typedef typename std::array<BlinkingLedConfig, N>::size_type size_type;

    int _flagIndex;
    BlinkingLed *blinkingLed;
    std::array<BlinkingLedConfig, N> blinkingLedConfigs;
    std::array<bool, N> errorFlags;

    void selectBlinkingLedConfig() {
        for (size_type i = 0; i < errorFlags.size(); i++) {
            if (errorFlags[i]) {
                blinkingLed->setConfig(cloneConfigWithExitMillis(blinkingLedConfigs[i]));
                return;
            }
        }

        blinkingLed->setConfig(BlinkingLed::ON);
    }

    BlinkingLedConfig cloneConfigWithExitMillis(BlinkingLedConfig config) {
        BlinkingLedConfig newConfig = config;
        newConfig.exitMillis = config.exitMillis + millis();
        return newConfig;
    }

public:
    MultipleErrorLed(BlinkingLed *blinkingLed,
                     std::array<BlinkingLedConfig, N> blinkingLedConfigs) :
            blinkingLed(blinkingLed), blinkingLedConfigs(blinkingLedConfigs) {
        for (int i = 0; i < errorFlags.size(); i++) {
            errorFlags[i] = false;
        }
    }

    void setErrorFlag(int flagIndex) {
        errorFlags[flagIndex] = true;
    }

    void clearErrorFlag(int flagIndex) {
        errorFlags[flagIndex] = false;
    }

    void setup() override {
        blinkingLed->setup();
    }

    void run() override {
        selectBlinkingLedConfig();
        blinkingLed->run();
    }
};


#endif //IOT_IOTCOMMONS_MULTIPLEERRORLED_H
