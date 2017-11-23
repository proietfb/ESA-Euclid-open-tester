#include "tm_acq_mng.h"
#include "tm_acq_manager.h"

static TM_acquisition* tm_instance = nullptr;

void lazyTM(){
  if(tm_instance == nullptr){
    tm_instance = new TM_acquisition();
  }
}

#ifdef __cplusplus
extern "C" {
#endif

  uint32_t icu_tm_acq_mng_initialize(const icu_tm_acq_manager_conf_t* config){
    lazyTM();
    tm_instance->initialize(config);
    return 0;
  }

  uint32_t icu_tm_acq_set_mode_one_shot(){
    tm_instance->set_mode_one_shot();
    return 0;
  }

  uint32_t icu_tm_acq_set_mode_cyclic(const uint16_t acquisition_cycle){
    tm_instance->set_mode_cyclic(acquisition_cycle);
    return 0;
  }
  
  uint32_t icu_tm_acq_mng_load_whole_tm_id_table(const uint32_t number_of_tms, const uint32_t tm_ids[]){
    tm_instance->load_whole_tm_id_table(number_of_tms, tm_ids);
    return 0;
  }

  uint32_t icu_tm_acq_mng_start_tm_acq(){

    if ((tm_instance->buffer1Loaded == true) && (tm_instance->tm_data_buffer_1.locked == false)) {
      tm_instance->buffer1Loaded = false; 
      tm_instance->start_tm_acquisition(tm_instance->tm_data_buffer_1);
    } else {
      tm_instance->buffer1Loaded = true;
      tm_instance->start_tm_acquisition(tm_instance->tm_data_buffer_2);
    }
    return 0; 
  }

  uint32_t icu_tm_acq_mng_stop_tm_acq(){

    tm_instance->stop_tm_acquisition();
    return 0;
  }
  
  uint32_t icu_tm_acq_mng_get_tms(uint32_t number_of_ids, uint16_t p_tm_ids[]){
    if (tm_instance->tm_data_buffer_1.inUse == false){
      tm_instance->get_tms(tm_instance->tm_data_buffer_1.size, tm_instance->tm_data_buffer_1);
    } else {
      tm_instance->get_tms(tm_instance->tm_data_buffer_2.size, tm_instance->tm_data_buffer_2);
    }
    return 0;
  }

  void icu_tm_acq_mng_reset(){
    tm_instance->reset();
  }
  
#ifdef __cplusplus
}
#endif
  
