#include "tm_acq_manager.h"
#include "fwa_gwa_motor_drv.h"
#include "spi_driver.h"

auto spiTM = Spi_driver::instance();

TM_acquisition::TM_acquisition() {}

void TM_acquisition::printBuffer(DataBuffer buffer){
    for(auto i: buffer.data_buffer){
    std::cout << i.id << "\n";
    if(i.id == 0){
      break;
    }
  }
}

uint32_t TM_acquisition::initialize(const icu_tm_acq_manager_conf_t *config) {

  spiTM->spi_write<uint16_t>(adc_addr, adc_data);

  return 0;
}

uint32_t TM_acquisition::load_whole_tm_id_table(const uint32_t number_of_tms,
                                                const uint32_t tm_ids[]) {
  for (uint32_t i = 0; i < number_of_tms; ++i) {

    switch (tm_ids[i]) {
    case NI_SA_TMP_1_CRYO:
      tm_ID_buffer[i].id = NI_SA_TMP_1_CRYO;
      break;
    case NI_SA_TMP_2_CRYO:
      tm_ID_buffer[i].id = NI_SA_TMP_2_CRYO;
      break;
    case NI_SA_TMP_3_CRYO:
      tm_ID_buffer[i].id = NI_SA_TMP_3_CRYO;
      break;
    case NI_SA_TMP_4_CRYO:
      tm_ID_buffer[i].id = NI_SA_TMP_4_CRYO;
      break;
    case NI_SA_TMP_5_CRYO:
      tm_ID_buffer[i].id = NI_SA_TMP_5_CRYO;
      break;
    case NI_SA_TMP_6_CRYO:
      tm_ID_buffer[i].id = NI_SA_TMP_6_CRYO;
      break;
    case NI_CSS_TMP_1_CRYO:
      tm_ID_buffer[i].id = NI_CSS_TMP_1_CRYO;
      break;
    case NI_CSS_TMP_2_CRYO:
      tm_ID_buffer[i].id = NI_CSS_TMP_2_CRYO;
      break;
    case NI_SSS_TMP_1_CRYO:
      tm_ID_buffer[i].id = NI_SSS_TMP_1_CRYO;
      break;
    case NI_SSS_TMP_2_CRYO:
      tm_ID_buffer[i].id = NI_SSS_TMP_2_CRYO;
      break;
    case NI_FWA_TMP_CRYO:
      tm_ID_buffer[i].id = NI_FWA_TMP_CRYO;
      break;
    case NI_GWA_TMP_CRYO:
      tm_ID_buffer[i].id = NI_GWA_TMP_CRYO;
      break;
    case NI_SA_TMP_1_FR:
      tm_ID_buffer[i].id = NI_SA_TMP_1_FR;
      break;
    case NI_SA_TMP_2_FR:
      tm_ID_buffer[i].id = NI_SA_TMP_2_FR;
      break;
    case NI_SA_TMP_3_FR:
      tm_ID_buffer[i].id = NI_SA_TMP_3_FR;
      break;
    case NI_SA_TMP_4_FR:
      tm_ID_buffer[i].id = NI_SA_TMP_4_FR;
      break;
    case NI_SA_TMP_5_FR:
      tm_ID_buffer[i].id = NI_SA_TMP_5_FR;
      break;
    case NI_SA_TMP_6_FR:
      tm_ID_buffer[i].id = NI_SA_TMP_6_FR;
      break;
    case NI_CSS_TMP_1_FR:
      tm_ID_buffer[i].id = NI_CSS_TMP_1_FR;
      break;
    case NI_CSS_TMP_2_FR:
      tm_ID_buffer[i].id = NI_CSS_TMP_2_FR;
      break;
    case NI_SSS_TMP_1_FR:
      tm_ID_buffer[i].id = NI_SSS_TMP_1_FR;
      break;
    case NI_SSS_TMP_2_FR:
      tm_ID_buffer[i].id = NI_SSS_TMP_2_FR;
      break;
    case FWA_MOT_PHA_I:
      tm_ID_buffer[i].id = FWA_MOT_PHA_I;
      break;
    case FWA_MOT_PHB_I:
      tm_ID_buffer[i].id = FWA_MOT_PHB_I;
      break;
    case GWA_MOT_PHA_I:
      tm_ID_buffer[i].id = GWA_MOT_PHA_I;
      break;
    case GWA_MOT_PHB_I:
      tm_ID_buffer[i].id = GWA_MOT_PHB_I;
      break;
    case NI_CU_LED_V_1:
      tm_ID_buffer[i].id = NI_CU_LED_V_1;
      break;
    case NI_CU_LED_V_2:
      tm_ID_buffer[i].id = NI_CU_LED_V_2;
      break;
    case NI_CU_LED_V_3:
      tm_ID_buffer[i].id = NI_CU_LED_V_3;
      break;
    case NI_CU_LED_V_4:
      tm_ID_buffer[i].id = NI_CU_LED_V_4;
      break;
    case NI_CU_LED_V_5:
      tm_ID_buffer[i].id = NI_CU_LED_V_5;
      break;
    case ICU_5V:
      tm_ID_buffer[i].id = ICU_5V;
      break;
    case ICU_5V_CURRENT:
      tm_ID_buffer[i].id = ICU_5V_CURRENT;
      break;
    case CMD_MOT_HS_READ_REQ:
      tm_ID_buffer[i].id = CMD_MOT_HS_READ_REQ;
      break;
    case END_OF_TABLE:
      tm_ID_buffer[i].id = END_OF_TABLE;
      break;
    default:
      break;
    }
  }
  return 0;
}

uint32_t TM_acquisition::set_mode_one_shot() {

  return 0;
}

uint32_t TM_acquisition::set_mode_cyclic(const uint16_t acquisition_cycle) {
  
  return 0;
}

uint32_t TM_acquisition::start_tm_acquisition(DataBuffer dataBuffer) {

  for (uint8_t i = 0; i < tm_ID_buffer.size(); ++i) {
    spiTM->spi_write_tm(tm_ID_buffer[i].id);
    usleep(10);
    if (tm_ID_buffer[i].id == END_OF_TABLE) {
      dataBuffer.size = i;
      break;
    }
  }
  usleep(10);
  spiTM->spi_write<uint16_t>(adc_addr, adc_data);
  bool parityMsg = true;
  dataBuffer.inUse = true;

  for (uint8_t i = 0; i < tm_ID_buffer.size(); ++i) {
    if (parityMsg) {
      spiTM->spi_read_tm();
      parityMsg = false;
    }
    dataBuffer.data_buffer[i].array_id[0] = spiTM->spi_read_tm();
    dataBuffer.data_buffer[i].array_id[1] = spiTM->spi_read_tm();
    if (dataBuffer.data_buffer[i].id == 0) {
      // parity messages
      spiTM->spi_read_tm();
      usleep(10);
      spiTM->spi_read_tm();
      usleep(10);
      spiTM->spi_read_tm();
      usleep(10);
      printBuffer(dataBuffer);
      dataBuffer.inUse = false;
      break;
    }
  }
  return 0;
}

uint32_t TM_acquisition::stop_tm_acquisition() { return 0; }

uint32_t TM_acquisition::get_tms(const uint32_t number_of_ids, // da controllare
                                 DataBuffer dataBuffer) {
  dataBuffer.locked = true;
  for(auto i: dataBuffer.data_buffer){
    std::cout << i.id << "\n";
    if(i.id == 0){
      break;
    }
  }
  dataBuffer.locked = false;
  return 0;
}

uint32_t TM_acquisition::reset() {

  tm_ID_buffer.fill({0});
  tm_data_buffer_1.inUse = false;
  tm_data_buffer_1.locked = false;
  tm_data_buffer_1.size = 0;
  tm_data_buffer_1.data_buffer.fill({0});
  tm_data_buffer_2.inUse = false;
  tm_data_buffer_2.locked = false;
  tm_data_buffer_2.size = 0;
  tm_data_buffer_2.data_buffer.fill({0});
  return 0;
}
