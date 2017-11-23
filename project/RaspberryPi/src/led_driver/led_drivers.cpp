#include "led_drivers.h"

auto spiLed = Spi_driver::instance();

Led_drivers::Led_drivers(){}

icu_led_drv_status_t ledStatus;

uint32_t Led_drivers::initialize(const uint32_t max_duty_cycle,	const uint32_t delay){

  LEDConfLock = false;

  if(!LEDConfLock){
    ledStatus.maximum_duty = max_duty_cycle;
    ledStatus.sync_delay = delay;
    LEDConfLock = true;
  }
  spiLed->spi_write<uint16_t>(LedConfAddr::ledConf1, ledConf1_4_data);
  return 0;
}

uint32_t Led_drivers::start_excitation(const uint32_t identifier,const uint8_t current_level, const uint32_t duty_cycle){

  //calculate the pwm duty cycle
  ledStatus.status = 1;
  ledStatus.current_level = current_level;
  ledStatus.duty = duty_cycle;

  switch(identifier){
  case LED_1:
    spiLed->spi_write<uint16_t>(ledConnectAddress, LedConnect::led1);
    break;
  case LED_2:
    spiLed->spi_write<uint16_t>(ledConnectAddress, LedConnect::led2);
    break;
  case LED_3:
    spiLed->spi_write<uint16_t>(ledConnectAddress, LedConnect::led3);
    break;
  case LED_4:
    spiLed->spi_write<uint16_t>(ledConnectAddress, LedConnect::led4);
    break;
  case LED_5:
    spiLed->spi_write<uint16_t>(ledConnectAddress, LedConnect::led5);
    break;
  default:
    break;
  }
  spiLed->spi_write<uint16_t>(ledConnectAddress, duty_cycle);

  return 0;
}

uint32_t Led_drivers::stop_excitation(){

  ledStatus.current_level = 0;
  ledStatus.duty = 0;
  ledStatus.status = 0;

  spiLed->spi_write<uint16_t>(ledConnectAddress, LedConnect::led_all_disconnect);
  
  return 0;
}

uint32_t Led_drivers::reset(){

  ledStatus.current_level = 0;
  ledStatus.duty = 0;
  ledStatus.status = 0;

  spiLed->spi_write<uint16_t>(resetFPGA, 0x00);
 
  return 0;
}

uint32_t Led_drivers::get_status(icu_led_drv_status_t* p_status_reg){
  return 0;
}
