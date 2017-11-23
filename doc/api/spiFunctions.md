# SPI 

## Master side Spi functions

All files located in `~/RaspberryPi/src/spi_driver/` are used to start and manage communication between master and slave. 
`spi_driver.h` and `spi_driver.cpp` are library functions written in C++, and `spi_drv.h` and `spi_drv.cpp` are necessary to interface library with Application Software.

### spi_driver functions

All functions return 0 if works fine.

|function prototype| Description |
|------------------|-------------|
|uint32\_t spi_initialize()| declare and open spi master device and set clock protocol|
|template <class T> uint32\_t spi\_write(uint8\_t address, T data)| spi_write is a c++ template class because we need to send two types of messages: negatives are used to set stepper anti-clockwork mode and positive to rest. This functions takes as input address of DAS driver where data have to be stored.|
|uint32\_t spi\_write\_tm(uint32\_t message)|This function is used to send an uint32\_t data representing which telemetry need to be read.|
|uint8\_t spi\_read\_tm()| After that an TM message is sent, spi\_read\_tm() receives messages from slave with TM results.|
|static Spi\_driver* instance()| instatiate a static spi object.|

### Slave side spi functions

`spiSlaveManager.h` and `spiSlaveManager.cpp` are located in `~/SPISlave/src/SPISlave/` and are used to manage messages sent from master.

|function prototype| Description |
|------------------|-------------|
|SpiSlaveManager() | costructor of SpiSlaveManager class define Arduino as Slave device and set related spi pin as MISO mode.|
|bool isByteReceived() | If true this function reports that a new message has been stored in SPDR register.|
|void readData() | Reads spi command and depending on message call related function. |
|void atomicMode() |Handles messages that belong to spi atomic class.|
|void spiDataManager(uint8\_t adress, uint16\_t data)|When a spi atomic message is received, this function process it or sets related mode. It take as input address and data parameters that are the same that are sent from master.|
|void tmReceiveMode() |If master requests values of TMs, this function store which components have to process and set tmSendMode().|
|void tmSendMode() | When all TMs are evaluated this function sends them to master.|
|void stepperMode()| when a specific spi stepper command is came in, stepper mode is set to listen new messages about motor current level.|

