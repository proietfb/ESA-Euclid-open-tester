#ifndef HEATER_MANAGER_H
#define HEATER_MANAGER_H

#include <Arduino.h>
#include <stdint.h>
class HeaterManager {
  
    const uint8_t minValue_ = 0;
    const uint8_t maxValue_ = 255;
    uint8_t ledPin_;
    uint32_t configValue_;
    uint16_t currentValue_;

    HeaterManager(uint8_t ledPin, uint8_t startValue);
    void heaterInitialize();
    void setHeater(uint16_t setValue);

    static HeaterManager* fpa;
    static HeaterManager* sa;
   
  public:

    enum HeaterSpiCommands {
      HEATER_CONF1 = 512,
      HEATER_CONF2 = 33288,
      HEATER_RESET = 281,
      HEATER_FPA = 283,
      HEATER_SA = 285
    };
    bool initialized = false;

    static HeaterManager* instanceFPA();
    static HeaterManager* instanceSA();

    void spiDataHeaters(uint16_t address, uint16_t data);
    void reset();

};
#endif

