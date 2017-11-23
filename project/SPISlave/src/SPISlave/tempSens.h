#ifndef TEMP_SENS_MANAGER_H
#define TEMP_SENS_MANAGER_H

#include "dht.h"
#include <Arduino.h>
#include <stdint.h>
#include <time.h>

class TempSensManager {

  uint8_t tempPin_;
  uint16_t checkTemp();

public:
  TempSensManager(uint8_t tempPin);

  uint32_t randomKelvin(uint8_t rangeMin, uint16_t rangeMax);
};
#endif
