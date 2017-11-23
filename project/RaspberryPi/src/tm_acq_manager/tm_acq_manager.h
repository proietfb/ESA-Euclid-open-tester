#ifndef TM_ACQ_MANAGER_H
#define TM_ACQ_MANAGER_H

#include "tm_acq_mng.h"
#include <array>

class TM_acquisition {

  const uint8_t adc_addr = 77;
  const uint16_t adc_data = 0xA800;

  template <typename T> union Tm_ids {
    T id;
    uint8_t array_id[sizeof(T)];
  };

  std::array<Tm_ids<uint32_t>, 255> tm_ID_buffer;

public:
  bool buffer1Loaded = true;
  
  struct DataBuffer {
    bool inUse = false;
    bool locked = false;
    uint8_t size;
    std::array<Tm_ids<uint16_t>, 255> data_buffer;
  } tm_data_buffer_1, tm_data_buffer_2;

  TM_acquisition();

  void printBuffer(DataBuffer buffer);
  
  uint32_t initialize(const icu_tm_acq_manager_conf_t* config);

  uint32_t load_whole_tm_id_table(const uint32_t number_of_tms, const uint32_t tm_ids[]);

  uint32_t set_mode_one_shot();

  uint32_t set_mode_cyclic(const uint16_t acquisition_cycle);

  uint32_t start_tm_acquisition(DataBuffer dataBuffer);

  uint32_t stop_tm_acquisition();

  uint32_t get_tms(const uint32_t number_of_ids, DataBuffer dataBuffer);

  uint32_t reset();

};


#endif
