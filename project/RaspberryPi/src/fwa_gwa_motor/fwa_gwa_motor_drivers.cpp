#include "fwa_gwa_motor_drivers.h"
#include "spi_driver.h"

auto spiMotor = Spi_driver::instance();

icu_fwa_gwa_status_t status_t;
icu_fwa_gwa_phase_status_t phase_status_t;

Fwa_gwa_motor_drivers::Fwa_gwa_motor_drivers() {}

uint32_t Fwa_gwa_motor_drivers::initialize() {

  spiMotor->spi_write<uint16_t>(MotorConfAddr::conf1, MotorConfData::data1_2);
  spiMotor->spi_write<uint16_t>(MotorConfAddr::conf2, MotorConfData::data1_2);
  spiMotor->spi_write<uint16_t>(MotorConfAddr::conf3,
                                MotorConfData::data3_4_7_8);
  spiMotor->spi_write<uint16_t>(MotorConfAddr::conf4,
                                MotorConfData::data3_4_7_8);
  spiMotor->spi_write<uint16_t>(MotorConfAddr::conf5, MotorConfData::data5_6);
  spiMotor->spi_write<uint16_t>(MotorConfAddr::conf6, MotorConfData::data5_6);
  spiMotor->spi_write<uint16_t>(MotorConfAddr::conf7,
                                MotorConfData::data3_4_7_8);
  spiMotor->spi_write<uint16_t>(MotorConfAddr::conf8,
                                MotorConfData::data3_4_7_8);

  return 0;
}

uint32_t Fwa_gwa_motor_drivers::reset()
{

  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr2,
                                MotorControlData::disconnectBoth);
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1,
                                MotorControlData::bridgeDisable);
  enable_current_protection(TRUE);
  status_t.drv_exec_status = MotorDriverStatus::disable;

  return 0;
}

uint32_t Fwa_gwa_motor_drivers::energize(const uint32_t motor_id, int8_t energization_phase_a, int8_t energization_phase_b)
{
  
  //std::cout << "motor_id: "<<motor_id << "\n";
  if (status_t.drv_exec_status == MotorDriverStatus::on) {
    deenergize();
  }
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1, MotorControlData::bridgeEnable);
  if (motor_id == MotorID::fwa) {
    //std::cout << "connect fwa"  << "\n";
    spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr2, MotorControlData::connectFWA);
  } else if (motor_id == MotorID::gwa) {
    //std::cout << "connect gwa" << "\n";
    spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr2, MotorControlData::connectGWA);
  }
  usleep(2);
  spiMotor->spi_write<int16_t>(MotorControlAddr::setCurrent, 0);
  spiMotor->spi_write<int16_t>(MotorControlAddr::setCurrent, 0);
  status_t.drv_exec_status = MotorDriverStatus::on;
  usleep(7);
  //spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1, MotorControlData::bridgeEnable);
  usleep(2);
  //std::cout << "ph a" << "\n";
  spiMotor->spi_write<int16_t>(MotorControlAddr::setCurrent, energization_phase_a);
  //std::cout << "ph_b" << "\n";
  spiMotor->spi_write<int16_t>(MotorControlAddr::setCurrent, energization_phase_b);
  //std::cout << "go microstep" << "\n";
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1,
                                MotorControlData::selEnableClk1);
  usleep(15);

  return 0;
}

uint32_t Fwa_gwa_motor_drivers::execute_profile(const uint16_t microstep_number, const icu_fwa_gwa_microstep_t *p_microsteps)
{
  // previous step, load profile
  energize(MotorID::gwa, p_microsteps->phase_a, p_microsteps->phase_b);
  // wait until profile is executed
  sleep(5);
  deenergize();
  return 0;
}

void Fwa_gwa_motor_drivers::stop() {}

uint32_t Fwa_gwa_motor_drivers::execute_single_microstep(const uint32_t motor_id, icu_fwa_gwa_microstep_t *microstep)
{
  energize(motor_id, microstep->phase_a, microstep->phase_b);
  return 0;
}

uint32_t Fwa_gwa_motor_drivers::deenergize()
{
  // std::cin>> a;
  //std::cout << "deen pha" << "\n";
  spiMotor->spi_write<int16_t>(MotorControlAddr::setCurrent, 0);
  // std::cin>> a;
  //std::cout << "deen phb" << "\n";
  spiMotor->spi_write<int16_t>(MotorControlAddr::setCurrent, 0);
  usleep(22);
  //std::cout << "disconnect both" << "\n";
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr2, MotorControlData::disconnectBoth);
  usleep(2);
  //std::cout << "disable bridge" << "\n";
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1, MotorControlData::bridgeDisable);
  usleep(2);
  status_t.drv_exec_status = MotorDriverStatus::safe;
  //std::cout << status_t.drv_exec_status << "\n";
  return 0;
}

uint32_t Fwa_gwa_motor_drivers::enable_current_protection(const bool_t do_enable)
{

  if (do_enable == TRUE) {
    spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1, MotorControlData::protectionEnable);
  } else {
    spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1, MotorControlData::protectionDisable);
  }
  return 0;
}

uint32_t Fwa_gwa_motor_drivers::hs_state_read(const uint32_t motor_id, uint8_t detection_threshold, bool_t *hs_input_1, bool_t *hs_input_2)
{
  if (motor_id == MotorID::fwa) {
    std::cout << "FWA"  << "\n";
    spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr2, MotorControlData::hsConnectFWA);
  } else if (motor_id == MotorID::gwa) {
    std::cout << "GWA"  << "\n";
    spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr2, MotorControlData::hsConnectGWA);
  }
  //std::cin >> a;
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1, MotorControlData::hsPowerON);
  usleep(1);
  //std::cin >> a;
  if (motor_id == MotorID::fwa) {
    spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1, MotorControlData::hsResetLatches1);
    sleep(5);
  }
  if (motor_id == MotorID::gwa) {
    spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1, MotorControlData::hsResetLatches2);
    sleep(5);
  }
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr3, MotorControlData::motHSReadReq);
  usleep(10);
  //std::cin >> a;
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr1, MotorControlData::hsPowerOFF);
  usleep(1);
  //std::cin >> a;
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr2, MotorControlData::hsDisconnectBoth);
  usleep(1);
  //  std::cin >> a;
  spiMotor->spi_write<uint16_t>(MotorControlAddr::controlAddr3, MotorControlData::motHSReadReq);
  

  return 0;
}
