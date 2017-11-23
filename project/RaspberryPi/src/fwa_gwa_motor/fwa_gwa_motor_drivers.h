#ifndef FWA_GWA_MOTOR_DRIVERS_H
#define FWA_GWA_MOTOR_DRIVERS_H

//#include <stdint.h>
#include "fwa_gwa_motor_drv.h"

class Fwa_gwa_motor_drivers{

  enum MotorID {
    fwa = 0,
    gwa = 1
  };

  enum MotorDriverStatus{
    safe,
    disable,
    on
  };
  
  enum MotorConfAddr{
    conf1 = 32,
    conf2,
    conf3,
    conf4,
    conf8 = 51,
    conf7,
    conf5,
    conf6
  };

  enum MotorConfData{
    data1_2 = 0x8382,
    data3_4_7_8 = 0x100,
    data5_6 = 0x3C2
  };

  enum MotorControlAddr{
    setCurrent = 41, //original
    controlAddr1 = 64,//converted hex 0x40
    controlAddr2 = 47,//original spi 0x47
    controlAddr3 = 48// original spi 0x48
  };

  enum MotorControlData{
    disconnectBoth = 0x0800,
    connectFWA = 0x8801,
    connectGWA = 0x8804,
    selEnableClk1 = 0xE801,
    selEnableClk2 = 0x6800,
    hsDisconnectBoth = 0x0D00,
    hsConnectFWA = 0x8D04,
    hsConnectGWA = 0x8D10,
    hsPowerON = 0xE701,
    hsPowerOFF = 0x6700,
    hsResetLatches1 = 0x6901,
    hsResetLatches2 = 0xE900,
    bridgeEnable = 0xC501,
    bridgeDisable = 0x4500,
    protectionEnable = 0xC700,
    protectionDisable = 0x4701,
    motHSReadReq = 0x0000
  };
  
  public:

  uint16_t motorProfileSize;
  
  enum MotorProfile {
    idle = 0,
    execInProgress
  };
  
  Fwa_gwa_motor_drivers();

  uint32_t initialize();

  uint32_t reset();

  uint32_t energize(const uint32_t motor_id, int8_t energization_phase_a, int8_t
		    energization_phase_b);

  uint32_t execute_profile (const uint16_t microstep_number, const icu_fwa_gwa_microstep_t* p_microsteps);

  void stop();

  uint32_t execute_single_microstep(const uint32_t motor_id, icu_fwa_gwa_microstep_t* microstep);

  uint32_t deenergize();

  uint32_t enable_current_protection(const bool_t do_enable);

  uint32_t hs_state_read(const uint32_t motor_id, uint8_t detection_threshold, bool_t* hs_input_1, bool_t* hs_input_2);
			
};
#endif
