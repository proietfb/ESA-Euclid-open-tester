#ifndef SPI_SLAVE_MANAGER_H
#define SPI_SLAVE_MANAGER_H

#include <Arduino.h>
#include <array.hpp>
#include <stdint.h>

#include "StepperManager.h"
#include "TMManager.h"
#include "heaterManager.h"
#include "shiftRegManager.h"
#include "HsManager.h"

class SpiSlaveManager {

  TMManager tm_mng;

  enum SpiCommands : uint16_t { ADC_CONF_DATA = 43008, ADC_CONF_ADDR = 411 };

  enum class SpiMode : uint8_t { ATOMIC, TM_RECEIVE, TM_SEND, STEPPER };

  SpiMode spiModeActive = SpiMode::ATOMIC;
  bool receivedDone = false;
  uint8_t atomicMarker = 0;
  uint8_t tmReceiveMarker = 0;
  int8_t tmSendMarker = 0;
  uint16_t address;
  uint16_t data;

  std::array<uint8_t, 4> incomingData;

  enum class Steppers : uint8_t {FWA, GWA, NONE};
  Steppers stepperConnected;
  uint8_t stepperMarker;
  uint8_t microstepMarker = 0;
  int16_t stepperAddress;
  int16_t stepperData;
  
  std::array<int8_t, 4> incomingStepperData;

  void atomicMode();
  void tmReceiveMode();
  void tmSendMode();
  void stepperMode();
  void spiDataManager(uint16_t address, uint16_t data);
  void spiTMManager();

  void spiDataStepper(uint16_t address, uint16_t data);
  
public:
  SpiSlaveManager() {
    pinMode(MISO, OUTPUT);
    SPCR |= _BV(SPE);
  }

  bool isByteReceived() {
    if ((SPSR & _BV(SPIF)) != 0) {
      return true;
    }
    return false;
  }
  void spiReadData();
};
#endif
