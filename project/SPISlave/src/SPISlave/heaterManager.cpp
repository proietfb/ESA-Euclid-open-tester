#include "heaterManager.h"

HeaterManager* HeaterManager::fpa = nullptr; 
HeaterManager* HeaterManager::sa = nullptr;

HeaterManager::HeaterManager(uint8_t ledPin, uint8_t startValue): ledPin_(ledPin), currentValue_(startValue), configValue_(startValue) {}

HeaterManager* HeaterManager::instanceFPA(){
  if(!fpa){
    fpa = new HeaterManager(5,0);
  }
  return fpa;
}

HeaterManager* HeaterManager::instanceSA(){
  if(!sa){
    sa = new HeaterManager(3,127);
  }
  return sa;
}

void HeaterManager::spiDataHeaters(uint16_t address, uint16_t data){
  switch(address){
  case HeaterSpiCommands::HEATER_FPA:
    if(data == HeaterSpiCommands::HEATER_CONF1){
      heaterInitialize();
      Serial.println("config heater FPA");
    } else {
      setHeater(data);
      Serial.println("set heater FPA");
    }
    break;
  case HeaterSpiCommands::HEATER_SA:
    if(data == HeaterSpiCommands::HEATER_CONF2){
      heaterInitialize();
      Serial.println("config heater SA");
    } else {
      setHeater(data);
      Serial.println("set heater SA");
    }
    break;
  default:
    break;
  }
}


void HeaterManager::heaterInitialize() {
  
  initialized = true;
  pinMode(ledPin_, OUTPUT);
  analogWrite(ledPin_, configValue_);
}

void HeaterManager::setHeater(uint16_t setValue) {
  if (initialized){
    // 1024:maxValue = setValue:x
    uint32_t newValue = ((uint32_t)setValue * maxValue_) / 1024;
    analogWrite(ledPin_, newValue);
    currentValue_ = newValue;
  }
}

void HeaterManager::reset(){
  initialized = false;
  analogWrite(ledPin_, 0);
}
