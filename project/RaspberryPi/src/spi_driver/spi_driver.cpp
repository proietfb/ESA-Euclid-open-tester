#include "spi_driver.h"

Spi_driver::Spi_driver() {}

Spi_driver *Spi_driver::spi = NULL;

Spi_driver *Spi_driver::instance() {

  if (!spi) {
    spi = new Spi_driver();
  }
  return spi;
}

uint32_t Spi_driver::spi_initialize() {

  fd_ = open("/dev/spidev0.0", O_RDWR); // open device
  assert(fd_ >= 0);

  ret_ = ioctl(fd_, SPI_IOC_WR_MAX_SPEED_HZ, &speed_); // set commspeed
  assert(ret_ >= 0);
  return 0;
}

template <class T> uint32_t Spi_driver::spi_write(uint8_t address, T data) {

  uint8_t idSlave = 1;
  // address data + parity bit
  address <<= 1;
  std::bitset<8> bits(address);
  bits.set(0, 1);
  address = static_cast<uint8_t>(bits.to_ulong());

  dataBuffer.data =
      (static_cast<uint32_t>(idSlave << 24)) | (address << 16) | data;
  for (auto i : dataBuffer.bff) {
    struct spi_ioc_transfer spi_;
    memset(&spi_, 0, sizeof(spi_));
    spi_.tx_buf = reinterpret_cast<unsigned long>(&i);
    spi_.len = 1;
    ret_ = ioctl(fd_, SPI_IOC_MESSAGE(1), &spi_);
    assert(ret_ >= 1);
    //usleep(10);
  }

  return 0;
}

template uint32_t Spi_driver::spi_write<uint16_t>(uint8_t address,
                                                  uint16_t data);
template uint32_t Spi_driver::spi_write<int16_t>(uint8_t address, int16_t data);

uint32_t Spi_driver::spi_write_tm(uint32_t message) {

  union {
    uint32_t id;
    uint8_t array_id[4];
  } tm_id;

  tm_id.id = message;
  for (auto i : tm_id.array_id) {
    struct spi_ioc_transfer spi_;
    memset(&spi_, 0, sizeof(spi_));
    spi_.tx_buf = reinterpret_cast<unsigned long>(&i);
    spi_.len = 1;
    ret_ = ioctl(fd_, SPI_IOC_MESSAGE(1), &spi_);
    assert(ret_ >= 1);
    // usleep(10);
  }

  return 0;
}

uint8_t Spi_driver::spi_read_tm() {

  uint8_t rxValue;
  struct spi_ioc_transfer spiReceiveData_;
  memset(&spiReceiveData_, 0, sizeof(spiReceiveData_));

  spiReceiveData_.tx_buf = static_cast<unsigned long>(sendValueToReceive_);
  spiReceiveData_.rx_buf = reinterpret_cast<unsigned long>(&rxValue);

  spiReceiveData_.len = 1;
  ret_ = ioctl(fd_, SPI_IOC_MESSAGE(1), &spiReceiveData_);
  assert(ret_ >= 1);

  return rxValue;
}

uint32_t Spi_driver::spi_read(uint8_t address, uint16_t *data) {
  /*unsigned char rxValue;
  struct spi_ioc_transfer spiReceiveData_;
  memset(&spiReceiveData_, 0, sizeof(spiReceiveData_));

    for(int i=0; i< 5; ++i){	//WARNING valore a caso
    spiReceiveData_.tx_buf = (unsigned long) sendValueToReceive_;
    spiReceiveData_.rx_buf = (unsigned long) &rxValue;

    receiveBuffer.vector.push_back(rxValue);
    spiReceiveData_.len = 1;
    ret_ = ioctl(fd_,SPI_IOC_MESSAGE(1), &spiReceiveData_);
    assert(ret_ >= 1);
    }*/
  return 0;
}
