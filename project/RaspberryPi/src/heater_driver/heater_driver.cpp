#include "heater_driver.h"

auto spiHeater = Spi_driver::instance();

Heater_driver::Heater_driver(){}

uint32_t Heater_driver::initialize(){
  spiHeater->spi_write<uint16_t>(heaterFPA, heaterConf1);
  spiHeater->spi_write<uint16_t>(heaterSA, heaterConf2);
  return 0;
}

uint32_t Heater_driver::switch_on(uint8_t identifier, uint16_t duty_cycle_in_ticks){
  spiHeater->spi_write<uint16_t>(identifier, duty_cycle_in_ticks);
  return 0;
}

uint32_t Heater_driver::switch_off(uint8_t identifier){
  spiHeater->spi_write<uint16_t>(identifier, 0x0);
  return 0;
}

uint32_t Heater_driver::reset(){
  spiHeater->spi_write<uint16_t>(resetHeaters, 0x0);
  return 0;
}
