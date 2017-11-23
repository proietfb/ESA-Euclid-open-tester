# SPI basic code on Arduino Uno

As Raspberry Pi either Arduino Uno is equipped with a full SPI interface. There is also a SPI library but cannot set Arduino as slave device. So for our purpose we use three physical registers:
- SPCR: SPI Control Register has 8 bits, each of which is used to control a specific SPI setting. 
- SPDR: we will use SPI Data Register to read incoming data from master and outgoing replies to it. It is composed of one shift register and one received buffer both of 8 bits width.
- SPSR: SPI Status Register define its status based on microcontroller condition. For example set SPIF mask when a data is written on SPDR.

As with Raspberry Pi we don't need to set all SPI options because clock is driven from master, and on ATMEGA328P SPI mode and bit order have default values respectively 0 and MSB.

So we have to define Arduino as slave device and MISO line as output; on setup function we define:

```c++
pinMode(MISO,OUTPUT);
SPCR |= _BV(SPE);
```
Second above line is composed by Atmel macro  `_BV(SPE)` that's like `(1<<SPE)` to enable SPI interface on device; this operation set Arduino as slave too because 4th bit of SPCR is default 0 (if 1 master mode is enabled). For more information on SPCR register see this [page](https://www.arduino.cc/en/Tutorial/SPIEEPROM).

With SPDR we can read and write SPI data.

`i = SPDR` allow to save 8 bits word contained in SPDR register and with `SPDR = i` we write i's value on shift register.

There are two ways to verify if a word is written on SPDR register from master: using polling or interrupt.

The choice depends on application that should be developed. Interrupt creates an extra overhead because we enter and exit continuously from an ISR, polling instead control if SPIF mask placed on SPSR changed from 0 to 1. In loop function we place if/then structure to check this value:
```c++
if((SPSR & _BV(SPIF)) != 0){
	//do something
}
```
If 7th bit of SPSR is 1 something was written in SPDR; at the end of transaction SPIF mask return automatically 0.

Below there is full basic Arduino Uno code:
```c++
#include "spiSlaveManager.h"


SpiSlaveManager spiSM = SpiSlaveManager(); // SPI class

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
    
    //put your code here

  }
}
```
spiSlaveManager.h

```c++
#ifndef SPI_SLAVE_MANAGER
#define SPI_SLAVE_MANAGER

#include "Array.h"
#include <Arduino.h>

class SpiSlaveManager {
  public:
    struct InOutBufferData_ { //utility buffer to save SPI incoming data
      Array<byte, 5> bufferData_;
      int bufferPosition_;
    };
    InOutBufferData_ inOutbf_;
    
  public:
    SpiSlaveManager();

    bool isByteReceived(); //returns if a byte is written on SPDR    
};
#endif
```
spiSlaveManager.cpp

```c++
#include "spiSlaveManager.h"

SpiSlaveManager::SpiSlaveManager() {
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  // turn on SPI in slave mode. SPCR determine Arduino SPI settings
  SPCR |= _BV(SPE);
}

bool SpiSlaveManager::isByteReceived() {
  if ((SPSR & _BV(SPIF)) != 0) {
    return true;
  }
  else
    return false;
}
```

To creare a buffer for incoming data I also used a small library which implements a STL Array structure. From this [link](https://github.com/janelia-arduino/Array) you should get Array.h and Array.cpp and include header file on spiSlaveManager.h. 


## References:
- [Arduino bitmask](https://www.arduino.cc/en/Tutorial/BitMask);
- [Arduino SPIEEPROM](https://www.arduino.cc/en/Tutorial/SPIEEPROM)
- [raspiduino](http://robotics.hobbizine.com/raspiduino.html)
- [janelia-arduino Array](https://github.com/janelia-arduino/Array)

Go back to [summary](../summary.md).
