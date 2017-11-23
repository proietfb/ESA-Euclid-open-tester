#include "fwa_gwa_motor_drivers.h"
#include "fwa_gwa_motor_drv.h"

static Fwa_gwa_motor_drivers* motor_instance = nullptr;

void lazyMotor(){
  if(motor_instance == nullptr){
    motor_instance = new Fwa_gwa_motor_drivers();
  }
}

#ifdef __cplusplus
extern "C" {
#endif

  uint32_t icu_fwa_gwa_drv_initialize(){
    return motor_instance->initialize();
  }

  uint32_t icu_fwa_gwa_drv_reset(){
    return motor_instance->reset();
  }

  uint32_t icu_fwa_gwa_drv_energize (const uint32_t motor_id, int8_t energization_phase_a, int8_t energization_phase_b) {
    return motor_instance->energize(motor_id, energization_phase_a, energization_phase_b);
  }

  uint32_t icu_fwa_gwa_drv_execute_profile (const uint16_t microstep_number,const icu_fwa_gwa_microstep_t * p_microsteps){
    return motor_instance->execute_profile(microstep_number, p_microsteps);
  }

  void icu_fwa_gwa_drv_stop() {
    return motor_instance->stop();
  }

  uint32_t icu_fwa_gwa_drv_execute_single_microstep (const uint32_t motor_id, icu_fwa_gwa_microstep_t* microstep){
    return motor_instance->execute_single_microstep(motor_id, microstep);
  }

  uint32_t icu_fwa_gwa_drv_deenergize (){
    return motor_instance->deenergize();
  }

  uint32_t icu_fwa_gwa_drv_enable_current_protection (const bool_t do_enable){
    return motor_instance->enable_current_protection(do_enable);
  }

  uint32_t icu_fwa_gwa_drv_hs_state_read (const uint32_t motor_id, uint8_t detection_threshold, bool_t* hs_input_1, bool_t* hs_input_2){
    return motor_instance->hs_state_read(motor_id, detection_threshold, hs_input_1, hs_input_2);
  }
  
#ifdef __cplusplus
}
#endif
