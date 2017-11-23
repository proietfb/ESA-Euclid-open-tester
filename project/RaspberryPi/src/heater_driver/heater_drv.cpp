#include "heater_driver.h"
#include "heater_drv.h"

static Heater_driver* heater_instance = nullptr;

void lazyHeater(){
  if(heater_instance == nullptr){
    heater_instance = new Heater_driver();
  }
}

static const uint8_t heater_fpa = Heater_driver::heaterFPA;
static const uint8_t heater_sa = Heater_driver::heaterSA;

int retFunction;

#ifdef __cplusplus
extern "C" {
#endif

  uint32_t icu_heater_initialize(){
    lazyHeater();
    retFunction = heater_instance->initialize();
    return retFunction;
  }
  uint32_t icu_heater_switch_on(const icu_heater_id_t identifier, const uint32_t duty_cycle_in_ticks){
    
    if(identifier == HEATER_FPA){
      retFunction = heater_instance->switch_on(heater_fpa, (uint16_t) duty_cycle_in_ticks);
    } else if(identifier == HEATER_SA) {
      retFunction = heater_instance->switch_on(heater_sa, (uint16_t) duty_cycle_in_ticks);
    }
    return retFunction;
  }
  uint32_t icu_heater_switch_off(const icu_heater_id_t identifier){
    if(identifier == HEATER_FPA){
      retFunction = heater_instance->switch_off(heater_fpa);
    } else if(identifier == HEATER_SA){
      retFunction = heater_instance->switch_off(heater_sa);
    }
    return retFunction;
  }
  uint32_t icu_heater_reset(){
    return heater_instance->reset();
  }
  
#ifdef __cplusplus
}
#endif
