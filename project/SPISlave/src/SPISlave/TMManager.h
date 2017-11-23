#ifndef TM_MANAGER_H
#define TM_MANAGER_H

#include <Arduino.h>

#include "libs/array.hpp"
#include "shiftRegManager.h"
#include "tempSens.h"
#include "HsManager.h"
#include "StepperManager.h"

class TMManager {

  TempSensManager tempSens{8};

public:
  TMManager();

  enum tm_ID_values : uint32_t {
    NI_SA_TMP_1_CRYO = 0x00F78140,
      NI_SA_TMP_2_CRYO = 0x00F70141,
      NI_SA_TMP_3_CRYO = 0x00F70142,
      NI_SA_TMP_4_CRYO = 0x00F78143,
      NI_SA_TMP_5_CRYO = 0x00F70144,
      NI_SA_TMP_6_CRYO = 0x00F78145,
      NI_CSS_TMP_1_CRYO = 0x00F70136,
      NI_CSS_TMP_2_CRYO = 0x00F78137,
      NI_SSS_TMP_1_CRYO = 0x00F70148,
      NI_SSS_TMP_2_CRYO = 0x00F78149,
      NI_FWA_TMP_CRYO = 0x00F7812A,
      NI_GWA_TMP_CRYO = 0x00F7012B,
      NI_SA_TMP_1_FR = 0x00F78120,
      NI_SA_TMP_2_FR = 0x00F70121,
      NI_SA_TMP_3_FR = 0x00F70122,
      NI_SA_TMP_4_FR = 0x00F78123,
      NI_SA_TMP_5_FR = 0x00F70124,
      NI_SA_TMP_6_FR = 0x00F78125,
      NI_CSS_TMP_1_FR = 0x00F78126,
      NI_CSS_TMP_2_FR = 0x00F70127,
      NI_SSS_TMP_1_FR = 0x00F70128,
      NI_SSS_TMP_2_FR = 0x00F78129,
      NI_FWA_TMP_FR = 0x00F7812A,
      NI_GWA_TMP_FR = 0x00F7012B,
      FWA_MOT_PHA_I = 0x08F7822F,
      FWA_MOT_PHB_I = 0x08F7023F,
      GWA_MOT_PHA_I = 0x08F7824F,
      GWA_MOT_PHB_I = 0x08F7025F,
      NI_CU_LED_V_1 = 0x10F7026F,
      NI_CU_LED_V_2 = 0x10F7827F,
      NI_CU_LED_V_3 = 0x10F7828F,
      NI_CU_LED_V_4 = 0x10F7029F,
      NI_CU_LED_V_5 = 0x10F702AF,
      ICU_5V = 0x08F782BF,
      ICU_5V_CURRENT = 0x08F702CF,
      MOTOR_HS_READ_REQ = 0x40C80000,
      END_OF_TABLE = 0X00000000
      };

  template <typename T> union tm_IDs {
    T id;
    uint8_t array_id[sizeof(T)];
  };

  struct Tm_buffer {
    uint8_t index;
    std::array<tm_IDs<uint32_t>, 20> buffer_id;
  } tm_buffer;

  struct Tm_result {
    uint8_t index;
    std::array<tm_IDs<uint16_t>, 20> buffer_id;
  } tm_result;

  uint8_t tmSize = 0;
  

  void fillResultBuffer(Tm_buffer bufferData);
  void printBuffer(Tm_buffer buffer);
};

#endif
