#ifndef ICU_FWA_GWA_MOTORS_H
#define ICU_FWA_GWA_MOTORS_H

//#include <public/fpga_addresses.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef unsigned int bool_t;

#define TRUE 1UL
#define FALSE 0UL
  
  /** FWA MOTOR ID */
#define 	FWA_MOTOR_ID  (0UL)

  /** GWA MOTOR ID */
#define 	GWA_MOTOR_ID  (1UL)

  /* profile_exec_status */
#define 	MOTOR_PROFILE_IDLE  			0x0U
#define 	MOTOR_PROFILE_EXEC_IN_PROGRESS  0x1U

  /* drv_exec_status */
#define 	MOTOR_DRV_SAFE_STATE  		0x0U
#define 	MOTOR_DRV_CONTROL_DISABLE  	0x1U
#define 	MOTOR_DRV_CONTROL_ON  		0x2U

  typedef struct
  {
    uint16_t	microstep_time;
    int8_t		phase_a;
    int8_t		phase_b;
  }
    icu_fwa_gwa_microstep_t;

  typedef struct{

    uint32_t	profile_exec_status;
    uint32_t 	drv_exec_status;
  }
    icu_fwa_gwa_status_t;

  typedef struct
  {
    int8_t 		direct_phase_a_current_output;
    int8_t 		direct_phase_b_current_output;
    uint16_t 	direct_microstep_exec_time;
    int8_t 		direct_microstep_exec_phase_a_current;
    int8_t 		direct_microstep_exec_phase_b_current;
  }
    icu_fwa_gwa_phase_status_t;

  typedef struct
  {
    bool_t spw_sequence;
    bool_t spw_escape;
    bool_t spw_parity;
    bool_t spw_credit;
    bool_t spw_disconnect;
    bool_t spw_eep_detected;
    bool_t unexpected_profile_data_received;
    bool_t profile_fifo_edac_uncorrectable;
    bool_t profile_fifo_overflow;
    bool_t lut_edac_uncorrectable;
    bool_t size_error;
    bool_t profile_fifo_underflow;
  }
    icu_fwa_gwa_errors_t;

  uint32_t icu_fwa_gwa_drv_get_status (icu_fwa_gwa_status_t * status, icu_fwa_gwa_phase_status_t  * phase_status,	uint16_t * number_of_microsteps_executed, icu_fwa_gwa_microstep_t * last_microstep_in_execution, icu_fwa_gwa_errors_t * execution_errors);

  uint32_t icu_fwa_gwa_drv_initialize(void);

  uint32_t icu_fwa_gwa_drv_reset(void);

  uint32_t icu_fwa_gwa_drv_energize (const uint32_t motor_id, int8_t energization_phase_a, int8_t energization_phase_b);

  uint32_t icu_fwa_gwa_drv_execute_profile (const uint16_t microstep_number,const icu_fwa_gwa_microstep_t * p_microsteps);

  void icu_fwa_gwa_drv_stop(void);

  uint32_t icu_fwa_gwa_drv_execute_single_microstep (const uint32_t motor_id, icu_fwa_gwa_microstep_t* microstep);

  uint32_t icu_fwa_gwa_drv_deenergize (void);

  uint32_t icu_fwa_gwa_drv_enable_current_protection (const bool_t do_enable);

  uint32_t icu_fwa_gwa_drv_load_lut_tables(const uint16_t phase_a_lut_data[], const uint16_t phase_b_lut_data[], bool_t enable_luts);

  uint32_t icu_fwa_gwa_drv_hs_state_read (const uint32_t motor_id, uint8_t detection_threshold, bool_t* hs_input_1, bool_t* hs_input_2);

  uint32_t icu_fwa_gwa_drv_get_hw_alarms(bool_t* vref_prot, bool_t* motor_pwm_prot_ph_a, bool_t* motor_pwm_prot_ph_b, bool_t* motor_driver);

#ifdef __cplusplus
}
#endif
  
#endif // ICU_FWA_GWA_MOTORS_H
