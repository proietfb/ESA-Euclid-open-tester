#ifndef HEATER_DRIVER_H
#define HEATER_DRIVER_H

#include <stdint.h>
#include "spi_driver.h"

class Heater_driver{
  
 public:
  // defines the values to be used as first parameter in all the functions of the driver
  // that require an identifier of the heater

  static const uint8_t heaterFPA = 13;
  static const uint8_t heaterSA = 14;
  static const uint8_t resetHeaters = 12;
  
  static const uint16_t heaterConf1 = 0X0200;
  static const uint16_t heaterConf2 = 0X8208;

  Heater_driver();

  //Initiaizes the heater diver; it sends SPI commands to HEATER_CONFx with the constant values declared
  //in HW/SW ICD
  uint32_t initialize();
		
  //allows switching on a selected heater by configuring the PWM duty cycle through an SPI command
  uint32_t switch_on(uint8_t identifier, uint16_t duty_cycle_in_ticks);

  //allows switching off a selected heater by configuring the PWM duty cycle through an SPI command
  uint32_t switch_off(uint8_t identifier);

  //resets the heater driver functionality
  uint32_t reset();

};

#endif
