#include "spiSlaveManager.h"
#include "StepperManager.h"

SpiSlaveManager spiSM = SpiSlaveManager();

//auto setfwa = StepperManager::instanceFWA();
//auto setgwa = StepperManager::instanceGWA();

void setup (void) {
  Serial.begin(9600);
}

void loop (void) {
  if(spiSM.isByteReceived()){
    spiSM.spiReadData();
  }
}
