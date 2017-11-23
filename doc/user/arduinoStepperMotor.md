# Manage an 28BYJ-48 stepper motor using SPI communication

This example want to connect a stepper motor to Arduino and manage it with Raspberry Pi using SPI communication.

## Requirements
- Arduino Uno
- raspberry Pi
- stepper Motor 28BYJ-48
- wires
- (optional) External power supply

## Stepper Motor 28BYJ-48
Stepper motor is a motor controlled by a series of electroagnetics coils. The center shaft has a series of magnets mounted on it, and the coils surrounding the shaft are alternatively given current or not, creating magnetic fields which repulse or attract the magnets on the shaft, causing the motor to rotate. There are two types of stepper motor: unipolar steppers and bipolar steppers; 28BYJ-48 is a unipolar stepper because power always comes in on this one pole.
This motor can be driven using many drivers but most common is ULN2003. It makes a connection between Arduino and stepper motor using six pins: 4 digital pins (one per coil), ground pin and 5V pin for supply power. Chip where ULN2003 driver is contained has also 4 led that each of one is an indicator of when a phase is active. Below there is a configuration example.

![alt text](./img/user/arduinoStepperMotor.png)

Before talking about code we have to know something else about this stepper: it has a gear ratio of 32 and Stride Angle 5.625°. Using these information we can calculate number of steps: `nSteps = nStepsOfOneRevolution*GearRatio`; with numbers `steps = (360°/5.625°)*32 = 2048` This value is important when we will use on Arduino sketch

## Arduino code

```c++
#include "spiSlaveManager.h"
#include "StepperManager.h"

SpiSlaveManager spiSM = SpiSlaveManager(); // SPI class
StepperManager stepperM1(32, 6, 7, 8, 9, 700);

void setup (void) {

  Serial.begin (9600);

  //SPI position buffer initialization
  spiSM.inOutbf_.bufferPosition_ = 0;

  delay(10);
}

void loop (void) {
  if (spiSM.isByteReceived()) { //if byte has been received
    
    if (spiSM.inOutbf_.bufferPosition_ < spiSM.inOutbf_.bufferData_.size())
      spiSM.inOutbf_.bufferPosition_++;
    else {
      spiSM.inOutbf_.bufferPosition_ = 0;
      spiSM.inOutbf_.bufferData_.clear();
    }

    byte data = SPDR; // read SPI data register
    spiSM.inOutbf_.bufferData_.push_back(data); //fill incomingBufferData

    Serial.print("buffPos ");
    Serial.println(spiSM.inOutbf_.bufferPosition_);

    if (spiSM.inOutbf_.bufferData_[spiSM.inOutbf_.bufferPosition_] == '9')
      stepperM1.runMotor();
  }
}
```

StepperManager.h

```c++
#ifndef STEPPER_MANAGER
#define STEPPER_MANAGER

#include<Arduino.h>
#include<Stepper.h>

class StepperManager {
  public:
    int stepsPerRevolution_;
    int in1_;
    int in2_;
    int in3_;
    int in4_;
    int speedMotor_;
  public:
    StepperManager(int stepsPerRevolution, int in1, int in2, int in3, int in4, int speedMotor);

    void runMotor();
};
#endif
```

StepperManager.cpp

```c++
#include "StepperManager.h"

Stepper stepperOne;

StepperManager::StepperManager(int stepsPerRevolution, int in1, int in2, int in3, int in4, int speedMotor) {
  stepsPerRevolution_ = stepsPerRevolution;
  in1_ = in1;
  in2_ = in2;
  in3_ = in3;
  in4_ = in4;
  speedMotor_ = speedMotor;
  stepperOne = Stepper(stepsPerRevolution_, in1_, in2_, in3_, in4_);

}

void StepperManager::runMotor() {
  long Steps2Take  =  2048 ;  // Rotate CW 1 turn
  stepperOne.setSpeed(speedMotor_);   
  stepperOne.step(Steps2Take);
  delay(1000);
  
  Steps2Take  =  - 2048;  // Rotate CCW 1 turn  
  stepperOne.setSpeed(400); 
  stepperOne.step(Steps2Take);
  delay(2000);
}
```
We can command our stepper motor using Stepper library allowed by Arduino. First you should define a constructor passing the number of steps per revolution that has the stepper motor and the four digital pins which it is connected. `setSpeed(int)` method requires an int value and define speed rotation expressed in RPM. Finally, `step(int)` rotates shaft of a given steps. Notice that to rotate stepper motor on counter clockwise we have to use a negative value.

Note: To define `Stepper stepperOne` and then `StepperOne = Stepper(...)` I modified Arduino stepper library adding a blank constructor.

## Raspberry Pi code

This tutorial requires Master side basic [code](./spiSWbasicMaster.md).


## References
- [Fritzing modules](https://github.com/tardate/X113647Stepper/)
- [Instructables](http://www.instructables.com/id/BYJ48-Stepper-Motor/step3/Library-Direction-Issue-And-how-to-fix-it-/)
- [Arduino documentation for Stepper library](https://www.arduino.cc/en/Reference/Stepper)

Go back to [summary](../summary.md)
