#ifndef ICU_TM_ACQ_MANAGER_H
#define ICU_TM_ACQ_MANAGER_H

#include "fwa_gwa_motor_drv.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/* TM IDs */
#define NI_SA_TMP_1_CRYO		(0x00F78140UL)
#define NI_SA_TMP_2_CRYO 		(0x00F70141UL)
#define NI_SA_TMP_3_CRYO		(0x00F70142UL)
#define NI_SA_TMP_4_CRYO		(0x00F78143UL)
#define NI_SA_TMP_5_CRYO		(0x00F70144UL)
#define NI_SA_TMP_6_CRYO		(0x00F78145UL)
#define NI_CSS_TMP_1_CRYO		(0x00F70136UL)
#define NI_CSS_TMP_2_CRYO		(0x00F78137UL)
#define NI_SSS_TMP_1_CRYO		(0x00F70148UL)
#define NI_SSS_TMP_2_CRYO		(0x00F78149UL)
#define NI_FWA_TMP_CRYO			(0x00F7812AUL)
#define NI_GWA_TMP_CRYO			(0x00F7012BUL)

#define NI_SA_TMP_1_FR			(0x00F78120UL)
#define NI_SA_TMP_2_FR			(0x00F70121UL)
#define NI_SA_TMP_3_FR			(0x00F70122UL)
#define NI_SA_TMP_4_FR			(0x00F78123UL)
#define NI_SA_TMP_5_FR			(0x00F70124UL)
#define NI_SA_TMP_6_FR			(0x00F78125UL)
#define NI_CSS_TMP_1_FR			(0x00F78126UL)
#define NI_CSS_TMP_2_FR			(0x00F70127UL)
#define NI_SSS_TMP_1_FR			(0x00F70128UL)
#define NI_SSS_TMP_2_FR			(0x00F78129UL)
#define NI_FWA_TMP_FR			(0x00F7812AUL)
#define NI_GWA_TMP_FR			(0x00F7012BUL)

#define FWA_MOT_PHA_I			(0x08F7822FUL)
#define FWA_MOT_PHB_I			(0x08F7023FUL)
#define GWA_MOT_PHA_I			(0x08F7824FUL)
#define GWA_MOT_PHB_I			(0x08F7025FUL)

#define NI_CU_LED_V_1			(0x10F7026FUL)
#define NI_CU_LED_V_2			(0x10F7827FUL)
#define NI_CU_LED_V_3			(0x10F7828FUL)
#define NI_CU_LED_V_4			(0x10F7029FUL)
#define NI_CU_LED_V_5			(0x10F702AFUL)

#define ICU_5V				(0x08F782BFUL)
#define ICU_5V_CURRENT			(0x08F702CFUL)
#define ICU_CDPU_TMP			(0x18F782DFUL)
#define ICU_LVPS_TMP			(0x18F782EFUL)

#define ASM_TSM1_GAIN			(0x08F7020FUL)
#define ASM_TSM1_OFFSET			(0x08F7821FUL)
#define SSS_CHAIN_CRYO_OFFSET	        (0x00F7814CUL)
#define SSS_CRYO_CHAIN_GAIN		(0x00F7014DUL)
#define CSS_CRYO_CHAIN_OFFSET 	        (0x00F7813EUL)
#define CSS_CRYO_CHAIN_GAIN		(0x00F7013FUL)

#define CMD_DAS_ALARMS_READ_REQ         (0x40CA0000UL)
#define CMD_MOT_HS_READ_REQ 	        (0x40C80000UL)

#define OBT_COARSE_HIGH			(0x60800000UL)
#define OBT_COARSE_LOW			(0x60810000UL)
#define OBT_FINE_HIGH			(0x60820000UL)
#define OBT_FINE_LOW			(0x60830000UL)
#define END_OF_TABLE			(0x00000000UL)

typedef struct{
  uint16_t settling_time_0; // time unit: 1 us
  uint16_t settling_time_1; // time unit: 1 us
  uint16_t settling_time_2; // time unit: 1 us
  uint16_t settling_time_3; // time unit: 1 us
  bool_t sync_acq_disable;
  uint32_t sync_acq_timeout; // time unit: 100 ns
  bool_t cyclic_mode_enable;
  uint16_t cyclic_period; // time unit: 1 ms
}
  icu_tm_acq_manager_conf_t;

typedef struct {
  bool_t sync_tm_disable;
  bool_t cyclic_mode;
  bool_t tm_buffer_data_available;
  bool_t tm_buffer_toggle_bit;
  bool_t tm_buffer_lock;
  bool_t running_state;
}
  icu_tm_acq_manager_status_t;

uint32_t icu_tm_acq_mng_initialize (const icu_tm_acq_manager_conf_t* config);

uint32_t icu_tm_acq_mng_load_whole_tm_id_table(const uint32_t number_of_tms, const uint32_t tm_ids[]);
uint32_t icu_tm_acq_set_mode_one_shot(void);

uint32_t icu_tm_acq_set_mode_cyclic(const uint16_t acquisition_cycle);

uint32_t icu_tm_acq_mng_enable_synchronization(const uint32_t sync_acq_timeout);

uint32_t icu_tm_acq_mng_disable_synchronization(void);

uint32_t icu_tm_acq_mng_start_tm_acq(void);

uint32_t icu_tm_acq_mng_stop_tm_acq(void);

uint32_t icu_tm_acq_mng_get_tms(const uint32_t number_of_ids, uint16_t p_tm_values[]);

uint32_t icu_tm_acq_mng_get_status (icu_tm_acq_manager_status_t * p_tm_acq_status);

uint32_t icu_tm_acq_mng_get_asynch_tm(const uint32_t tm_id, const uint32_t delay_ms, uint16_t * acquired_tm);

uint32_t icu_tm_acq_mng_read_asynch_tm_last_value(uint16_t* acquired_tm);

void icu_tm_acq_mng_reset(void);

#ifdef __cplusplus
}
#endif

#endif // ICU_TM_ACQ_MANAGER_H
