#include "spi_drv.h"
#include "spi_driver.h"

static Spi_driver *spi_instance = nullptr;

void lazySPI(){
  if(spi_instance == nullptr){
    spi_instance = Spi_driver::instance();
  }
}

#ifdef __cplusplus
extern "C" {
#endif

  uint32_t icu_spi_ctrl_initialize() {
    lazySPI();
    spi_instance->spi_initialize();
    return 0;
  }
  uint32_t icu_spi_ctrl_write(const uint8_t address, const uint16_t data) {
    //    spi_instance->spi_write(address, data);
    return 0;
  }
  uint32_t icu_spi_ctrl_read(const uint8_t address, uint16_t* data) {
    return 0;
  }
  
#ifdef __cplusplus
}
#endif
