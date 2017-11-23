#include "led_drv.h"
#include "led_drivers.h"

static Led_drivers* led_instance = nullptr;

void lazyLED(){
  if(led_instance == nullptr){
    led_instance = new Led_drivers();
  }
}

#ifdef __cplusplus
extern "C" {
#endif

  uint32_t icu_led_drv_initialize (const uint32_t max_duty_cycle, const uint32_t delay){
    lazyLED();
    return led_instance->initialize(max_duty_cycle, delay);  
  }

  uint32_t icu_led_drv_start_excitation(const uint32_t identifier, const uint8_t current_level, const uint32_t duty_cycle){
    return led_instance->start_excitation(identifier, current_level, duty_cycle);
  }

  uint32_t icu_led_drv_stop_excitation(){
    
    return led_instance->stop_excitation();
  }

  uint32_t icu_led_reset(){
    return led_instance->reset();
  }
  
  
#ifdef __cplusplus
}
#endif
