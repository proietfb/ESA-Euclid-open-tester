#include <stdio.h>

#include "fwa_gwa_motor_drv.h"
#include "heater_drv.h"
#include "led_drv.h"
#include "spi_drv.h"
#include "tm_acq_mng.h"

int main(int argc, char *argv[]) {

  int input;
  uint32_t data, led, hs;

  icu_heater_id_t heaterFPA = HEATER_FPA; // HEATER
  icu_heater_id_t heaterSA = HEATER_SA;   // HEATER
  const uint32_t max_duty_cycle = 512;    // LED
  const uint32_t delay = 500;             // LED
  bool_t boolTrue = TRUE;
  bool_t boolFalse = FALSE;
  bool_t *pTrue = &boolTrue;
  bool_t *pFalse = &boolFalse;

  //motor
  icu_fwa_gwa_microstep_t microstep;
  microstep.microstep_time = 8000;
  microstep.phase_a = 30;
  microstep.phase_b = -100;

  uint16_t profileSize = 3;
  icu_fwa_gwa_microstep_t steps[profileSize];
  steps[0].microstep_time = 7000;
  steps[0].phase_a = 100;
  steps[0].phase_b = -120;

  steps[1].microstep_time = 5000;
  steps[1].phase_a = -120;
  steps[1].phase_b = 120;

  steps[2].microstep_time = 6000;
  steps[2].phase_a = 50;
  steps[2].phase_b = 120;

  uint32_t hs_ids[] = {CMD_MOT_HS_READ_REQ, END_OF_TABLE};
  uint32_t number_of_hs = sizeof(hs_ids);
  // telemetries
  
  icu_tm_acq_manager_conf_t config_tm;
  icu_tm_acq_manager_status_t status_tm;

  config_tm.settling_time_0 = 50;
  config_tm.settling_time_1 = 50;
  config_tm.settling_time_2 = 50;
  config_tm.settling_time_3 = 50;
  config_tm.sync_acq_disable = TRUE;
  config_tm.sync_acq_timeout = 50;
  config_tm.cyclic_mode_enable = FALSE;
  config_tm.cyclic_period = 500;

  
  status_tm.sync_tm_disable = TRUE;
  status_tm.cyclic_mode = FALSE;
  status_tm.tm_buffer_data_available = FALSE;

  
  
  uint32_t tm_ids[] = {NI_SA_TMP_1_CRYO,NI_SA_TMP_2_CRYO,NI_SA_TMP_3_CRYO,END_OF_TABLE};
  uint32_t number_of_tms = sizeof(tm_ids);
  uint16_t tm_values[5] = {0,1,2,3,4}; //passare la vera tm

  //-----------------------

  printf("type 0 to initialize SPI \n");
  printf("type 1 to initialize heaters \n");
  printf("type 2 to switch on FPA \n");
  printf("type 3 to switch on SA \n");
  printf("type 4 to switch off FPA \n");
  printf("type 5 to switch off SA \n");
  printf("type 6 to reset all heaters \n");
  printf("type 7 to initizialize LED \n");
  printf("type 8 to connect and excitate led n \n");
  printf("type 9 to disconnect led \n");
  printf("type 10 to reset FPA LED driver \n");
  printf("type 11 to send motor profile \n");
  printf("type 12 to send microstep \n");
  printf("type 13 to use HS sensors \n");
  printf("type 14 to usemanage TM acquisitions\n");

  int done = 0;
  while (done == 0) {
    printf("insert command: ");
    scanf("%d", &input);
    switch (input) {
    case 0:
      icu_spi_ctrl_initialize();
      printf("SPI initialized\n");
      break;
    case 1:
      icu_heater_initialize();
      printf("heater initialized\n");
      break;
    case 2:
      printf("data: ");
      scanf("%i%", &data);
      icu_heater_switch_on(heaterFPA, data);
      printf("FPA switched on by %i \n", data);
      break;
    case 3:
      printf("data: ");
      scanf("%i%", &data);
      icu_heater_switch_on(heaterSA, data);
      printf("SA switched on by %i \n", data);
      break;
    case 4:
      icu_heater_switch_off(heaterFPA);
      printf("FPA switched off\n");
      break;
    case 5:
      icu_heater_switch_off(heaterSA);
      printf("SA switched off\n");
      break;
    case 6:
      icu_heater_reset();
      printf("reset all heaters\n");
      break;
    case 7:
      icu_led_drv_initialize(max_duty_cycle, delay);
      printf("LED initialized \n");
      break;
    case 8:
      printf("led: ");
      scanf("%i%", &led);
      printf("data: ");
      scanf("%i%", &data);
      icu_led_drv_start_excitation(led, 100, data);
      printf("led connected and excitated \n");
      break;
    case 9:
      icu_led_drv_stop_excitation();
      printf("all led disconnected \n");
      break;
    case 10:
      icu_led_reset();
      printf("led Driver resetted \n");
      break;
    case 11:
      icu_fwa_gwa_drv_initialize();
      //icu_fwa_gwa_drv_execute_single_microstep(GWA_MOTOR_ID, &microstep);
      int i;
      for(i = 0; i<profileSize; ++i){
      	icu_fwa_gwa_drv_execute_profile(profileSize, &steps[i]);
      }
      printf("motors profile to GWA \n");
      break;
    case 12:     
      icu_fwa_gwa_drv_initialize();
      icu_fwa_gwa_drv_execute_single_microstep(FWA_MOTOR_ID, &microstep);
      //int i;
      //for(i = 0; i<profileSize; ++i){
      //	icu_fwa_gwa_drv_execute_profile(profileSize, &steps[i]);
      //}
      printf("motors microstep to FWA \n");
      break;
    case 13:
      icu_fwa_gwa_drv_initialize();
      printf("hs (0:FWA ,1:GWA): ");
      scanf("%i%", &hs);
      if(hs == 0){
	icu_fwa_gwa_drv_hs_state_read(FWA_MOTOR_ID, 120, pTrue, pFalse);
      } else {
	icu_fwa_gwa_drv_hs_state_read(GWA_MOTOR_ID, 120, pTrue, pFalse);
      }
      sleep(1);
      icu_tm_acq_mng_initialize(&config_tm);
      icu_tm_acq_set_mode_one_shot();
      icu_tm_acq_mng_load_whole_tm_id_table(number_of_hs, hs_ids);
      icu_tm_acq_mng_start_tm_acq();
      //icu_tm_acq_mng_get_tms(5, tm_values);
      
      printf("hs Sensor \n");
      break;
    case 14:
      //one-shot mode
      icu_tm_acq_mng_initialize(&config_tm);
      if(config_tm.cyclic_mode_enable == FALSE){
	icu_tm_acq_set_mode_one_shot();
	icu_tm_acq_mng_load_whole_tm_id_table(number_of_tms, tm_ids);
	icu_tm_acq_mng_start_tm_acq();
	icu_tm_acq_mng_get_tms(5, tm_values);
      } else {
	icu_tm_acq_set_mode_cyclic(config_tm.cyclic_period);
	icu_tm_acq_mng_load_whole_tm_id_table(number_of_tms, tm_ids);
	icu_tm_acq_mng_start_tm_acq();
	icu_tm_acq_mng_get_tms(5, tm_values);
      }
      printf("tm acquisitions \n");
      break;
    case -1:
      done = 1;
      printf("exit");
      break;
    default:
      break;
    }
  }
  return 0;
}
