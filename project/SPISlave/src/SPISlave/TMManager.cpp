#include "TMManager.h"

auto ledTM = ShiftRegManager::instance();
auto hsFwaTM = HsManager::instanceHsFWA();
auto hsGwaTM = HsManager::instanceHsGWA();
auto fwaTM = StepperManager::instanceFWA();
auto gwaTM = StepperManager::instanceGWA();

TMManager::TMManager() {}

void TMManager::printBuffer(Tm_buffer buffer) {
  for (auto i : buffer.buffer_id) {
    Serial.print("Buffer: ");
    Serial.println(i.id);
    if (i.id == 0) {
      break;
    }
  }
}

void TMManager::fillResultBuffer(Tm_buffer bufferData) {
  for (uint8_t i = 0; i < bufferData.buffer_id.size(); ++i) {
    if (bufferData.buffer_id[i].id == tm_ID_values::END_OF_TABLE) {
      break;
    } else {
      switch (bufferData.buffer_id[i].id) {
      case tm_ID_values::NI_SA_TMP_1_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_SA_TMP_2_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_SA_TMP_3_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_SA_TMP_4_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_SA_TMP_5_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_SA_TMP_6_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_CSS_TMP_1_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 95);
        break;
      case tm_ID_values::NI_CSS_TMP_2_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 95);
        break;
      case tm_ID_values::NI_SSS_TMP_1_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_SSS_TMP_2_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_FWA_TMP_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_GWA_TMP_CRYO:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(120, 135);
        break;
      case tm_ID_values::NI_SA_TMP_1_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::NI_SA_TMP_2_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::NI_SA_TMP_3_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::NI_SA_TMP_4_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::NI_SA_TMP_5_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::NI_SA_TMP_6_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::NI_CSS_TMP_1_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::NI_CSS_TMP_2_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::NI_SSS_TMP_1_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::NI_SSS_TMP_2_FR:
        tm_result.buffer_id[i].id = tempSens.randomKelvin(87, 323);
        break;
      case tm_ID_values::FWA_MOT_PHA_I:
        tm_result.buffer_id[i].id = fwaTM->singleMicrostep[0];
        break;
      case tm_ID_values::FWA_MOT_PHB_I:
        tm_result.buffer_id[i].id = fwaTM->singleMicrostep[1];
        break;
      case tm_ID_values::GWA_MOT_PHA_I:
        tm_result.buffer_id[i].id = gwaTM->singleMicrostep[0];
        break;
      case tm_ID_values::GWA_MOT_PHB_I:
        tm_result.buffer_id[i].id = gwaTM->singleMicrostep[1];
        break;
      case tm_ID_values::NI_CU_LED_V_1:
        tm_result.buffer_id[i].id =
            ledTM->ledValues[ledTM->LedConnect::LED1].current_level_;
        break;
      case tm_ID_values::NI_CU_LED_V_2:
        tm_result.buffer_id[i].id =
            ledTM->ledValues[ledTM->LedConnect::LED2].current_level_;
        break;
      case tm_ID_values::NI_CU_LED_V_3:
        tm_result.buffer_id[i].id =
            ledTM->ledValues[ledTM->LedConnect::LED3].current_level_;
        break;
      case tm_ID_values::NI_CU_LED_V_4:
        tm_result.buffer_id[i].id =
            ledTM->ledValues[ledTM->LedConnect::LED4].current_level_;
        break;
      case tm_ID_values::NI_CU_LED_V_5:
        tm_result.buffer_id[i].id =
            ledTM->ledValues[ledTM->LedConnect::LED5].current_level_;
        break;
      case tm_ID_values::ICU_5V:
        tm_result.buffer_id[i].id = 5;
        break;
      case tm_ID_values::ICU_5V_CURRENT:
        tm_result.buffer_id[i].id = 265;
        break;
      case tm_ID_values::MOTOR_HS_READ_REQ:
	if(hsFwaTM->connected){
	  tm_result.buffer_id[i].id = hsFwaTM->lastHSRead;
	} else if (hsGwaTM->connected){
	  tm_result.buffer_id[i].id = hsGwaTM->lastHSRead;
	}
	break;
      default:
        break;
      }
    }
  }
}
