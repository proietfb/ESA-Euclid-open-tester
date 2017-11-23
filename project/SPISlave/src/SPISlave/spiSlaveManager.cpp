#include "spiSlaveManager.h"

auto ledDriver = ShiftRegManager::instance();
auto fwa = StepperManager::instanceFWA();
auto gwa = StepperManager::instanceGWA();
auto fpa = HeaterManager::instanceFPA();
auto sa = HeaterManager::instanceSA();
auto hsFWA = HsManager::instanceHsFWA();
auto hsGWA = HsManager::instanceHsGWA();

void SpiSlaveManager::spiReadData() {
  if (spiModeActive == SpiMode::ATOMIC) {
    atomicMode();
  } else if (spiModeActive == SpiMode::TM_RECEIVE) {
    tmReceiveMode();
  } else if (spiModeActive == SpiMode::TM_SEND) {
    tmSendMode();
  } else if (spiModeActive == SpiMode::STEPPER) {
    stepperMode();
  } else {}
}

void SpiSlaveManager::atomicMode(){
  switch (atomicMarker) {
  case 0:
    incomingData[3] = SPDR;
    ++atomicMarker;
    break;
  case 1:
    incomingData[2] = SPDR;
    ++atomicMarker;
    break;
  case 2:
    incomingData[1] = SPDR;
    ++atomicMarker;
    break;
  case 3:
    incomingData[0] = SPDR;
    atomicMarker = 0;

    address = (static_cast<uint16_t>(incomingData[0]) << 8) | (incomingData[1]);
    data = (static_cast<uint16_t>(incomingData[2]) << 8) | (incomingData[3]);
    // Serial.println(rcvbff.bff[0]);
    // Serial.println(rcvbff.bff[1]);
    // Serial.println(data);
    // Serial.print("address: ");
    //Serial.println(address);
    spiDataManager(address, data);
    break;
  default:
    break;
  }
}

void SpiSlaveManager::tmReceiveMode(){
  switch (tmReceiveMarker) {
  case 0:
    tm_mng.tm_buffer.buffer_id[tm_mng.tm_buffer.index].array_id[0] = SPDR;
    ++tmReceiveMarker;
    break;
  case 1:
    tm_mng.tm_buffer.buffer_id[tm_mng.tm_buffer.index].array_id[1] = SPDR;
    ++tmReceiveMarker;
    break;
  case 2:
    tm_mng.tm_buffer.buffer_id[tm_mng.tm_buffer.index].array_id[2] = SPDR;
    ++tmReceiveMarker;
    break;
  case 3:
    tm_mng.tm_buffer.buffer_id[tm_mng.tm_buffer.index].array_id[3] = SPDR;

    if (tm_mng.tm_buffer.buffer_id[tm_mng.tm_buffer.index].id ==
	tm_mng.tm_ID_values::END_OF_TABLE) {
      tm_mng.fillResultBuffer(tm_mng.tm_buffer);
      //tm_mng.printBuffer(tm_mng.tm_buffer);
      tmReceiveMarker = 0;
      tm_mng.tm_buffer.index = 0;
      spiModeActive = SpiMode::ATOMIC;
    } else {
      ++tm_mng.tm_buffer.index;
      tmReceiveMarker = 0;
    }
    break;
  default:
    break;
  }
}

void SpiSlaveManager::tmSendMode(){
  bool allDataSent = false;
  while(allDataSent == false){
    if ((SPSR & _BV(SPIF)) != 0){
      switch (tmSendMarker) {
      case 0:
	SPDR = tm_mng.tm_result.buffer_id[tm_mng.tm_result.index].array_id[0];
	++tmSendMarker;
	break;
      case 1:
	SPDR = tm_mng.tm_result.buffer_id[tm_mng.tm_result.index].array_id[1];
	if (tm_mng.tm_result.buffer_id[tm_mng.tm_result.index].id == 0) {
	  tm_mng.tm_result.index = 0;
	  tmSendMarker = 0;
	  allDataSent = true;
	  spiModeActive = SpiMode::ATOMIC;
	}
	else {
	  ++tm_mng.tm_result.index;
	  tmSendMarker = 0;
	}
	break;
      default:
	break;
      }
    }     
  }
}

void SpiSlaveManager::stepperMode() {
  switch(stepperMarker){
  case 0:
    incomingStepperData[3] = SPDR;
    stepperMarker++;
    break;
  case 1:
    incomingStepperData[2] = SPDR;
    stepperMarker++;
    break;
  case 2:
    incomingStepperData[1] = SPDR;
    stepperMarker++;
    break;
  case 3:
    incomingStepperData[0] = SPDR;
    stepperMarker = 0;
    stepperAddress = (static_cast<int16_t>(incomingStepperData[0]) << 8) | (incomingStepperData[1]);
    stepperData = (static_cast<int16_t>(incomingStepperData[2]) << 8) | (incomingStepperData[3]);

    if(stepperConnected == Steppers::FWA) {
      switch(microstepMarker) {
      case 0:
	//Serial.println("pha");
	fwa->singleMicrostep[0] = stepperData;
	microstepMarker++;
	break;
      case 1:
	//Serial.println("phb");
	fwa->singleMicrostep[1] = stepperData;
	microstepMarker = 0;
	if(stepperData != 0){
	  spiModeActive = SpiMode::ATOMIC;
	}
	break;
      default:
	break;
      }
    } else if (stepperConnected == Steppers::GWA){
      switch(microstepMarker) {
      case 0:
	gwa->singleMicrostep[0] = stepperData;
	microstepMarker++;
	break;
      case 1:
	gwa->singleMicrostep[1] = stepperData;
	microstepMarker = 0;
	if(stepperData != 0){
	  spiModeActive = SpiMode::ATOMIC;
	}
	break;
      default:
	break;
      }
	
    } else {}
    
    //Serial.println(stepperAddress);
    spiDataManager(stepperAddress, stepperData);
    
    break;
  default:
    break;
  }
}

void SpiSlaveManager::spiDataManager(uint16_t address, uint16_t data) {

  ledDriver->spiDataLeds(address, data);

  if (address == HeaterManager::HeaterSpiCommands::HEATER_FPA) {
    fpa->spiDataHeaters(address, data);
  } else if (address == HeaterManager::HeaterSpiCommands::HEATER_SA) {
    sa->spiDataHeaters(address, data);
  } else if (address == HeaterManager::HeaterSpiCommands::HEATER_RESET) {
    fpa->reset();
    sa->reset();
  }

  if (address == SpiCommands::ADC_CONF_ADDR) {
    if (receivedDone == false) {
      spiModeActive = SpiMode::TM_RECEIVE;
      receivedDone = true;
    } else {
      spiModeActive = SpiMode::TM_SEND;
      receivedDone = false;
    }
  }
  spiDataStepper(address, data);
}

void SpiSlaveManager::spiDataStepper(uint16_t address, uint16_t data){
  switch(address){
  case StepperManager::StepperSpiCommands::MOTOR_CONF1:
    //do something
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CONF2:
    //do something
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CONF3:
    //do something
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CONF4:
    //do something
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CONF5:
    //do something
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CONF6:
    //do something
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CONF7:
    //do something
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CONF8:
    //do something
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CTRL_ADDR_1:
    switch(data){
    case StepperManager::StepperSpiCommands::MOTOR_START_MICROSTEP:
      spiModeActive = SpiMode::ATOMIC;
      //convert phase a in # of steps
      if(stepperConnected == Steppers::FWA) {
	fwa->nSteps = ((fwa->singleMicrostep[0] * 4096)/127);
	fwa->runMotor(fwa->nSteps);
      } else if(stepperConnected == Steppers::GWA){
	gwa->nSteps = ((gwa->singleMicrostep[0] * 4096)/127);
	gwa->runMotor(gwa->nSteps);
      }
      break;
    case StepperManager::StepperSpiCommands::MOTOR_BRIDGE_ENABLE:
      //Serial.println("MB on");
      //Serial.println("done");
      break;
    case StepperManager::StepperSpiCommands::MOTOR_BRIDGE_DISABLE:
      //Serial.println("MB off");
      //Serial.println("done");
      break;
    case StepperManager::StepperSpiCommands::MOTOR_PROTECTION_ENABLE:
      //Serial.println("MP on");
      // Serial.println("done");
      break;
    case StepperManager::StepperSpiCommands::MOTOR_PROTECTION_DISABLE:
      //Serial.println("MP off");
      //Serial.println("done");
      break;
    case StepperManager::StepperSpiCommands::MOTOR_HS_POWER_ON:
      //Serial.println("motor hs on");
      //Serial.println("done");
      break;
    case StepperManager::StepperSpiCommands::MOTOR_HS_POWER_OFF:
      //Serial.println("motor hs power off");
      //Serial.println("done");
      break;
    case StepperManager::StepperSpiCommands::MOTOR_HS_RESET_LATCH_1:
      fwa->resetMotor(hsFWA);
      //Serial.println("reset HS latch 1");
      //Serial.println("done");
      break;
    case StepperManager::StepperSpiCommands::MOTOR_HS_RESET_LATCH_2:
      gwa->resetMotor(hsGWA);
      Serial.println("reset HS latch 2");
      //Serial.println("done");
      break;
    default:
      break;
    }
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CTRL_ADDR_2:
    switch (data){
    case StepperManager::StepperSpiCommands::MOTOR_DISCONNECT_BOTH:
      stepperConnected = Steppers::NONE;
      //Serial.println("motor disconnected");
      spiModeActive = SpiMode::ATOMIC;
      break;
    case StepperManager::StepperSpiCommands::MOTOR_CONNECT_FWA:
      spiModeActive = SpiMode::STEPPER;
      stepperConnected = Steppers::FWA;
      //delay(10);
      break;
    case StepperManager::StepperSpiCommands::MOTOR_CONNECT_GWA:
      spiModeActive = SpiMode::STEPPER;
      stepperConnected = Steppers::GWA;
      break;
    case StepperManager::StepperSpiCommands::MOTOR_HS_DISCONNECT_BOTH:
      hsFWA->connected = false;
      hsGWA->connected = false;
      //Serial.println("motor hs disconnected");
      break;
    case StepperManager::StepperSpiCommands::MOTOR_HS_CONNECT_FWA:
      hsFWA->connected = true;
      //Serial.println("motor hs connected");
      break;
    case StepperManager::StepperSpiCommands::MOTOR_HS_CONNECT_GWA:
      hsGWA->connected = true;
      break;
    default:
      break;
    }
    break;
  case StepperManager::StepperSpiCommands::MOTOR_CTRL_ADDR_3:
    if (data == StepperManager::StepperSpiCommands::MOTOR_HS_READ_REQ){
      if(hsFWA->connected){
	hsFWA->hsRead();
      } else if(hsGWA->connected){
	hsFWA->hsRead();
      } else{
	//tm
      }

    }
    break;
  default:
    break;
  }
}
