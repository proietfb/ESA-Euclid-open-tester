#ifndef LEDS_DRIVER_H
#define LEDS_DRIVER_H

#include <stdint.h>
#include "spi_driver.h"
#include "led_drv.h"

class Led_drivers {

  bool LEDConfLock = true;

  enum LedConnect{
    led1 = 0x0901,
    led2 = 0x0904,
    led3 = 0x0910,
    led4 = 0x0940,
    led5 = 0x0980,
    led_all_disconnect = 0x8900
  };

  const uint8_t ledConnectAddress = 71;
  const uint8_t resetFPGA = 11;

  
  enum LedConfAddr{
    ledConf1 = 36,
    ledConf2,
    ledConf3,
    ledConf4,
    ledConf5,
    ledConf6,
    ledConf7,
    ledConf8,
    ledConf9 = 15,
    ledConf10 = 4
  };
  
  const uint16_t ledConf1_4_data = 0x8342;
  const uint16_t ledConf5_8_data = 0x302;
  const uint16_t ledConf9_data = 0x8226;
  const uint16_t ledConf10_data = 0x0224;
  
  
 public:
    
  Led_drivers();

  //initialize the LED Module with a fixed that is assumed to be constant during mission
  uint32_t initialize(const uint32_t max_duty_cycle, const uint32_t delay);

  // Checks if starting a LED is possible, and if so it performs the "Start LED Excitation" sequence
  uint32_t start_excitation (const uint32_t identifier, const uint8_t current_level, const uint32_t duty_cycle);

  //Stop the LED excitation. It leaves the LEDs in an un-powered and un-selected configuration
  uint32_t stop_excitation();

  // Reset the FPGA LED functionality. It also stops the LED excitation. It leaves the LEDs ina an un-powered and un-selected configuration
  uint32_t reset();

  //Get the contents of register that contain state info
  uint32_t get_status (icu_led_drv_status_t* p_status_regs);
		
};

#endif
