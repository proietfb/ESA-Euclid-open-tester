#ifndef STEPPER_MANAGER
#define STEPPER_MANAGER

#include <Arduino.h>
#include "HsManager.h"

class StepperManager {

  int inPins[4];

  unsigned long lastTime;
  unsigned long time;
  
  const int nMaxSteps  = 4096;

  const int stepTime = 900;
  
  int step = 0;
  
  boolean clockwise = true;
  
  int stepsMatrix[8][4] = {
    {LOW, LOW, LOW, HIGH},
    {LOW, LOW, HIGH, HIGH},
    {LOW, LOW, HIGH, LOW},
    {LOW, HIGH, HIGH, LOW},
    {LOW, HIGH, LOW, LOW},
    {HIGH, HIGH, LOW, LOW},
    {HIGH, LOW, LOW, LOW},
    {HIGH, LOW, LOW, HIGH},
  };

  
  int arrayDefault[4] = {LOW, LOW, LOW, LOW};

  static StepperManager* fwa;
  static StepperManager* gwa;
  
  StepperManager(int in1, int in2, int in3, int in4);
  void writeStep(int outArray[4]);
  void stepper();
  void setDirection();
 
 public:

    enum StepperSpiCommands{
    SET_CURRENT = 65,
    MOTOR_CONF1 = 321,
    MOTOR_CONF2 = 323,
    MOTOR_CONF_DATA_1_2 = 33666,
    MOTOR_CONF3 = 325,
    MOTOR_CONF4 = 327,
    MOTOR_CONF8 = 359,
    MOTOR_CONF7 = 361,
    MOTOR_CONF_DATA_3_4_7_8 = 256,
    MOTOR_CONF5 = 363,
    MOTOR_CONF6 = 365,
    MOTOR_CONF_DATA_5_6 = 962,
    MOTOR_CTRL_ADDR_2 = 351,
    MOTOR_CTRL_ADDR_1 = 385,
    MOTOR_CTRL_ADDR_3 = 353,
    MOTOR_CONNECT_FWA = 34817,
    MOTOR_CONNECT_GWA = 34820,
    MOTOR_DISCONNECT_BOTH = 2048,
    MOTOR_START_MICROSTEP = 59393,
    MOTOR_BRIDGE_ENABLE = 50433,
    MOTOR_BRIDGE_DISABLE = 17664,
    MOTOR_PROTECTION_ENABLE = 50994,
    MOTOR_PROTECTION_DISABLE = 18177,
    MOTOR_HS_CONNECT_FWA = 36100,
    MOTOR_HS_CONNECT_GWA = 36112,
    MOTOR_HS_DISCONNECT_BOTH = 3328,
    MOTOR_HS_POWER_ON = 59137,
    MOTOR_HS_POWER_OFF = 26368,
    MOTOR_HS_RESET_LATCH_1 = 26881,
    MOTOR_HS_RESET_LATCH_2 = 59648,
    MOTOR_HS_READ_REQ = 0,
  };

    int32_t singleMicrostep[2];
    int32_t nSteps = 0;
    bool hsConnected = false;
    
    static StepperManager* instanceFWA();
    static StepperManager* instanceGWA();

    void runMotor(int nSteps);
    void resetMotor(HsManager* hs);
};
#endif
