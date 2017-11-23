# Telemetry Acquisition Manager

Tm acquistion manager aim to send a buffer of tms data and receive results from das board. 
Structures involved to this process are:
- Tm buffer: is a 4x255 bytes buffer filled each time that an acquisition is processed.
- Tm received data 1: is a 2x255 bytes buffer used to store values from das board.
- Tm received data 2: is a 2x255 bytes buffer like to previous buffer.
There are two data buffers because when one of them is involved to receive data is locked and can not be read.

## Tm Acquisition Manager Master Apis

All function to manage tm acquisitions are stored in `tm\_acq\_mananger.h`. All non-void functions without errors return 0.

|Fuction declaration| Description |
|-------------------|-------------|
|uint32\_t initialize(const icu\_tm\_acq\_manager\_conf\_t *config)| Sends an spi data to initialize das tm manager.|
|uint32\_t load\_whole\_tm\_id\_table(const uint32\_t number\_of\_tms,const uint32\_t tm\_ids[])| This funtions takes as input size of tm buffer and whole values which are ready to send out.|
|uint32\_t start\_tm\_acquisition(DataBuffer dataBuffer) | This function takes as input dataBuffer used to store tm results. First of all, all tm id are sent to das throw spi; then to syncronize messages with slave device icu sends a parity message and starts to listen receive values. When an EOT is received anoter three parity messages are sent to das. To avoid conflicts data buffer flag is enabled and disabled when all data are stored.|
|uint32\_t get\_tms(const uint32\_t number\_of\_ids, DataBuffer dataBuffer) | Read Tms values from data buffer which is not involved to send/receive process. |

## Tm Acquisition Manager Slave Apis

|Function declaration| Description |
|--------------------|-------------|
|void fillResultBuffer(Tm\_buffer bufferData)| After all tm messages are received, this function evaluates result and fill tm\_result buffer.|

