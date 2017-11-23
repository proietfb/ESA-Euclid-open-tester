#ifndef SHIFT_REG_MANAGER_H
#define SHIFT_REG_MANAGER_H

#include <Arduino.h>
#include <stdint.h>
#include "libs/array.hpp"

class ShiftRegManager {
    uint8_t latchPin_;
    uint8_t dataPin_;
    uint8_t clockPin_;
    uint8_t outputEnabledPin_;
    
    bool configFPGA = false;
        
    const uint8_t minValue_ = 0;
    const uint8_t maxValue_ = 255;

    enum LedSpiCommands{
      LED_CONF1 = 329,
      LED_CONF2 = 331,
      LED_CONF3 = 333,
      LED_CONF4 = 335,
      LED_CONF_DATA_1_4 = 33602,
      LED_CONF5 = 337,
      LED_CONF6 = 339,
      LED_CONF7 = 341,
      LED_CONF8 = 343,
      LED_CONF_DATA_5_8 = 770,
      LED_CONF9 = 287,
      LED_CONF_DATA_9 = 33318, 
      LED_CONF10 = 265,
      LED_CONF_DATA_10 = 548,
      LED_CONNECT = 399,
      LED1_DATA_CONNECT = 2305,
      LED2_DATA_CONNECT = 2308,
      LED3_DATA_CONNECT = 2320,
      LED4_DATA_CONNECT = 2368,
      LED5_DATA_CONNECT = 2432,
      LED_DATA_ALL_DISCONNECTED = 35072,
      LED_RESET = 279,
    };
  
    struct ledLevels{
      uint8_t current_level_;
      uint16_t dutyCycle_;
    };

    void ledExcitation();
    void reset();
    void setDutyCycle(uint16_t dutyCycle);
    void updateShiftRegister(uint8_t statusLeds);

    static ShiftRegManager* led;
    
    ShiftRegManager(uint8_t latchPin, uint8_t dataPin, uint8_t clockPin, uint8_t outputEnabledPin);
    
 public:

    static ShiftRegManager* instance();
    
    void spiDataLeds(uint16_t address, uint16_t data);
        
    enum LedConnect {
      LED1 = 0,
      LED2,
      LED3,
      LED4,
      LED5      
    };
    
    uint8_t ledConnected_ = 7; //all disconected
    std::array<ledLevels, 5> ledValues;
    
};
#endif

