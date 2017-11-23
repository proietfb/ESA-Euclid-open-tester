#include "tempSens.h"

TempSensManager::TempSensManager(uint8_t tempPin) : tempPin_(tempPin) {}

uint32_t TempSensManager::randomKelvin(uint8_t rangeMin, uint16_t rangeMax)
{
  uint16_t temp = 20;//checkTemp();
  uint16_t min = (rangeMin - temp);
  uint16_t max = (rangeMax - temp);
  return (random(min, max)) + temp;
}

uint16_t TempSensManager::checkTemp()
{
  dht dht;
  return dht.read11(tempPin_);
}
