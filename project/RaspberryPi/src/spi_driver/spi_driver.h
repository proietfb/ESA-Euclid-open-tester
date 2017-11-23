#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <array>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <cstdint>
#include <bitset>

class Spi_driver {
  
  const unsigned char sendValueToReceive_ = 0;
  int fd_;
  int ret_;
  const int speed_ = 100000;

  union {
    uint32_t data;
    uint8_t bff[4];
  } dataBuffer;

  static Spi_driver* spi;
   
 Spi_driver(); 
  
 public:
    
  static Spi_driver* instance();
  
  //this function initialize SPI driver, including sending SPI commands for PWM clocks configuration
  uint32_t spi_initialize();

  //writes an SPI command, with concurrent access control
  template<typename T> uint32_t spi_write(uint8_t address, T data);
   
  uint32_t spi_write_tm(uint32_t message);

  uint32_t spi_read(uint8_t address, uint16_t* data);

  uint8_t spi_read_tm();
  
  int closeFd(){
    return close(fd_);
  }
  
};

#endif
