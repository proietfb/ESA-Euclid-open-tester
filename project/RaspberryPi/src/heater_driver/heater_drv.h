#ifndef HEATER_DRV_H
#define HEATER_DRV_H

/*****************************************************************************
   APPLICATION INCLUDES
*****************************************************************************/
//#include <public/basic_types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	HEATER_FPA = 0,
	HEATER_SA
}
icu_heater_id_t;

uint32_t icu_heater_initialize(void);

uint32_t icu_heater_switch_on( const icu_heater_id_t identifier, const uint32_t duty_cycle_in_ticks);

uint32_t icu_heater_switch_off(const icu_heater_id_t identifier);

uint32_t icu_heater_reset(void);

#ifdef __cplusplus  
}
#endif

#endif
