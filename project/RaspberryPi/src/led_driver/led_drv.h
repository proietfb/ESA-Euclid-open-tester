#ifndef LEDS_H
#define LEDS_H

//#include <public/basic_types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  /**LED 1 Identifier*/
#define	LED_1  (0UL)
  /**LED 2 Identifier*/
#define	LED_2  (1UL)
  /**LED 3 Identifier*/
#define	LED_3  (2UL)
  /**LED 4 Identifier*/
#define	LED_4  (3UL)
  /**LED 5 Identifier*/
#define	LED_5  (4UL)
  
  typedef struct
  {
    uint32_t maximum_duty;
    uint32_t sync_delay;
    uint32_t current_level;
    uint32_t duty;
    uint32_t status;
    uint32_t irq_pending;
  }icu_led_drv_status_t;


  uint32_t icu_led_drv_initialize (const uint32_t max_duty_cycle, const uint32_t delay);
  uint32_t icu_led_drv_start_excitation (const uint32_t identifier,const uint8_t current_level, const uint32_t duty_cycle);

  uint32_t icu_led_drv_stop_excitation ();
  uint32_t icu_led_drv_reset ();
  uint32_t icu_led_drv_get_status (icu_led_drv_status_t * p_status_regs);

#ifdef __cplusplus
}
#endif
  
#endif
