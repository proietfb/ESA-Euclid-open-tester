# Serial Protocol Interface (SPI)

SPI is a synchronous serial communication interface used in short distance for embedded systems.
SPI devices communicate in full-duplex mode using master-slave architecture with single master and one or more slaves.

## SPI 4-wire interface buses, data transmission and SPI modes

This type of architecture has 4 logic signals:
1. SCLK: is a serial clock and it is an output from master;
2. MOSI: Master Output Slave Input is an output from master either and transmit bits from master to slave
3. MISO: Master Input Slave Output is used to send data from slave to master
4. SS: Slave Select
(Note: if a single slave is used and its permit it, SS pin can be fixed to logic low signal.)

![alt text][SPI4WIRES]

Master through MOSI line sends data to slave during each SPI clock cycle while slave sends infos on MISO bus.
Usually we have full-duplex transmissions that involve two shift registers with a given bit size connected in a virtual ring topologically.
So data are shifted out with most significant bit first (MSFIRST) from master to slave, and least significant bit first (LSFIRST) from slave to master.
Other than clock frequency, master must be select clock polarity and phase:
1. CPOL = 0: clock polarity correspond at 0 when master is in idle state and 1 when is active;
    1. CPHA = 0: data are captured on the rising clock edge and sent on the falling clock edge
    2. CPHA = 1: is a high to low transition.
2. CPOL = 1: is inversion to CPOL = 0, 1 is idle state and 0 active state;
    1. CPHA = 0: data are capture on falling clock edge and sent on rising time clock (high to low transition)
    2. CPHA = 1: is a low to high transition.

Then combining clock polarity and phase we have 4 types of SPI modes:

| SPI mode | Clock polarity | Clock phase | Clock edge |
| - | - | - | - |
| 0 | 0 | 0 | 1 |
| 1 | 0 | 1 | 0 |
| 2 | 1 | 0 | 1 |
| 3 | 1 | 1 | 0 |

## Others SPI configurations

### Independent	slave

In the independent slave configuration, we can connect several slaves to master each through an indipendent Slave Select pin. MISO, MOSI and clock are required to be tri-state pins. When master sends a message it can active one on more SS pins.

### Daisy Chain 

Daisy chain slave configuration uses just a SS pin but more slaves are connected to master. To send a message to a specific slave, master should create a package that contains ID slave device; all slaves will receive message but only that device will accept it.

## Reference:
- [wikipedia SPI](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus)

Go back to [summary](../summary.md)

[SPI4WIRES]: ./img/user-spi-M-S.png
