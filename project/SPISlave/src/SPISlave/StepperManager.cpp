#include "StepperManager.h"



StepperManager::StepperManager(int in1, int in2, int in3, int in4):
  inPins{in1, in2, in3, in4}
{
  pinMode(inPins[0], OUTPUT);
  pinMode(inPins[1], OUTPUT);
  pinMode(inPins[2], OUTPUT);
  pinMode(inPins[3], OUTPUT);
}

StepperManager* StepperManager::fwa = nullptr;
StepperManager* StepperManager::gwa = nullptr;

//auto HsLatch1 = HsManager::instanceHsFWA();
//auto HsLatch2 = HsManager::instanceHsGWA();

StepperManager* StepperManager::instanceFWA(){
  if(!fwa){
    fwa = new StepperManager(A0, A1, A2, A3);
  }
  return fwa;
}

StepperManager* StepperManager::instanceGWA(){
  if(!gwa){
    gwa = new StepperManager(A5, A6, A7, A8);
  }
  return gwa;
}

void StepperManager::runMotor(int nSteps) {
  unsigned long currentMicros;
  int stepsLeft = nSteps;
  time = 0;
  if (singleMicrostep[0] < 0) {
    clockwise = true;
    stepsLeft = abs(stepsLeft);
  } else {
    clockwise = false;
  }
  while (stepsLeft > 0) {
    currentMicros = micros();
    if (currentMicros - lastTime >= stepTime) {
      stepper();
      time += micros() - lastTime;
      lastTime = micros();
      stepsLeft--;
    }
  }
}

void StepperManager::resetMotor(HsManager* hs) {
  unsigned long currentMicros;
  int stepsLeft = 10000;
  time = 0;
  hs->firstHSRead;
  while (stepsLeft > 0) {
    hs->lastHSRead = hs->hsRead();
    if(hs->firstHSRead > hs->lastHSRead){
      break;  
    }
    currentMicros = micros();
    if (currentMicros - lastTime >= stepTime) {
      stepper();
      time += micros() - lastTime;
      lastTime = micros();
      stepsLeft--;
    }
  }
}

void StepperManager::writeStep(int outArray[4]) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(inPins[i], outArray[i]);
  }
}

void StepperManager::stepper() {
  if ((step >= 0) && (step < 8)) {
    writeStep(stepsMatrix[step]);
  } else {
    writeStep(arrayDefault);
  }
  setDirection();
}

void StepperManager::setDirection() {
  (clockwise) ? (step++) : (step--);
  if (step > 7) {
    step = 0;
  } else if (step < 0) {
    step = 7;
  }
}
