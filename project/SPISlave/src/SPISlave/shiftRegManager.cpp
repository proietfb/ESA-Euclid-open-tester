#include "shiftRegManager.h"

ShiftRegManager::ShiftRegManager(uint8_t latchPin, uint8_t dataPin, uint8_t clockPin, uint8_t outputEnabledPin):
  latchPin_(latchPin), dataPin_(dataPin), clockPin_(clockPin), outputEnabledPin_(outputEnabledPin) {

  pinMode(latchPin_, OUTPUT);
  pinMode(dataPin_, OUTPUT);
  pinMode(clockPin_, OUTPUT);
  pinMode(outputEnabledPin_, OUTPUT);
}

ShiftRegManager* ShiftRegManager::led = NULL;

ShiftRegManager* ShiftRegManager::instance(){
  if(!led){
    led = new ShiftRegManager(49, 48, 47, 6);
  }
  return led;
}
  

void ShiftRegManager::spiDataLeds(uint16_t address, uint16_t data){

  switch(address){
  case LedSpiCommands::LED_CONF1:
    //do something
    configFPGA = true;
    break;
  case LedSpiCommands::LED_CONF2:
    //do something
    break;
  case LedSpiCommands::LED_CONF3:
    //do something
    break;
  case LedSpiCommands::LED_CONF4:
    //do something
    break;
  case LedSpiCommands::LED_CONF5:
    //do something
    break;
  case LedSpiCommands::LED_CONF6:
    //do something
    break;
  case LedSpiCommands::LED_CONF7:
    //do something
    break;
  case LedSpiCommands::LED_CONF8:
    //do something
    break;
  case LedSpiCommands::LED_CONF9:
    //do something
    break;
  case LedSpiCommands::LED_CONF10:
    //do something
    break;
  case LedSpiCommands::LED_CONNECT:
    if(data == LedSpiCommands::LED1_DATA_CONNECT){
      ledConnected_ = LedConnect::LED1;
      ledValues[ledConnected_].current_level_ = 10;
    }
    else if (data == LedSpiCommands::LED2_DATA_CONNECT){
      ledConnected_ = LedConnect::LED2;
      ledValues[ledConnected_].current_level_ = 20;
    }
    else if (data == LedSpiCommands::LED3_DATA_CONNECT){
      ledConnected_ = LedConnect::LED3;
      ledValues[ledConnected_].current_level_ = 30;
    }
    else if (data == LedSpiCommands::LED4_DATA_CONNECT){
      ledConnected_ = LedConnect::LED4;
      ledValues[ledConnected_].current_level_ = 40;
    }
    else if (data == LedSpiCommands::LED5_DATA_CONNECT){
      ledConnected_ = LedConnect::LED5;
      ledValues[ledConnected_].current_level_ = 50;
    }
    else if (data == LedSpiCommands::LED_DATA_ALL_DISCONNECTED){

      for(uint8_t i; i<ledValues.size(); ++i){
	ledValues[i].dutyCycle_ = 0;
	ledValues[i].current_level_ = 0;
      }
      ledExcitation();
      ledConnected_ = 7; //all disconnected

    }
    else {
	ledValues[ledConnected_].dutyCycle_ = data;
	ledExcitation();
      }
    break;
  case LedSpiCommands::LED_RESET:

    ledValues[ledConnected_].dutyCycle_ = 0;
    ledValues[ledConnected_].current_level_ = 0;
    for(uint8_t i; i<ledValues.size(); ++i){
	ledValues[i].dutyCycle_ = 0;
	ledValues[i].current_level_ = 0;

      }
    Serial.println("led reset");
    ledExcitation();
    ledConnected_ = 7; //all disconnected
    //reset();
    break;
  default:
    break;
  }
}


void ShiftRegManager::setDutyCycle(uint16_t dutyCycle){
  int setValue = ((uint32_t)dutyCycle * maxValue_) /1024;
  analogWrite(outputEnabledPin_, maxValue_ - (uint8_t) setValue);
}

void ShiftRegManager::updateShiftRegister(uint8_t statusLeds) {
  uint8_t led = 0;
  digitalWrite(latchPin_, LOW);
  bitSet(led,statusLeds);
  shiftOut(dataPin_, clockPin_, MSBFIRST, led); //send data to shift register;
  digitalWrite(latchPin_, HIGH);
}

void ShiftRegManager::ledExcitation() {
  setDutyCycle(ledValues[ledConnected_].dutyCycle_);
  updateShiftRegister(ledConnected_);
}

void ShiftRegManager::reset(){

  setDutyCycle(ledValues[ledConnected_].dutyCycle_);
  updateShiftRegister(ledConnected_);
  configFPGA = false;

}
