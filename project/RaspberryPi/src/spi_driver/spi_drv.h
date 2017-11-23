#ifndef ICU_SPI_DRV_H
#define ICU_SPI_DRV_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t icu_spi_ctrl_initialize( void );
uint32_t icu_spi_ctrl_write(const uint8_t address, const  uint16_t data);
uint32_t icu_spi_ctrl_read(const uint8_t address, uint16_t * data);
    
#ifdef __cplusplus
}
#endif

#endif
