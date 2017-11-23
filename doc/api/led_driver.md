# Led Driver

Functions to manage led driver aim to manage calibration using LEDs.

## Led Driver Master functions

Master side functions are locate in `~/RaspberryPi/src/led_driver/`. All non-void functions return 0 fine work fine.

|Function Prototype| Description |
|------------------|-------------|
|uint32\_t initialize(const uint32\_t max\_duty\_cycle,	const uint32\_t delay)| This function initialize led status driver and sends led CONFIGx messages on slave throw SPI. Also takes as input max duty cycle, sync delay to set interface status and lock it to perform excitation procedure.|
|uint32\_t start\_excitation(const uint32\_t identifier,const uint8\_t current\_level, const uint32\_t duty\_cycle)| This functions takes as input led identifier, level of current and level of duty cycle to excitate led. Using spi atomic command we set led and duty cycle on led slave device.|
|uint32\_t stop\_excitation() | This function commands led driver to turn off led excitation.|
|uint32\_t reset() | Reset led driver. |

## Led Driver Slave functions

Slave functions are stored in `ShiftRegManager.h`.

|Function Prototype | Description |
|-------------------|-------------|
|ShiftRegManager() | Costructor of ShiftRegManager class set `latchPin_`, `dataPin_`, `clockPin_` and `outputEnabledPin_` as OUTPUT.|
|void spiDataLeds(uint8\_t address, uint16\_t data) | This function perform spi led atomic commands. Its inputs are address of led driver and data. Both are received throw spi command and are used to process icu request.|
|void setDutyCycle(uint16\_t dutyCycle)| This function take as input duty cycle value received from ICU and convert it on slave command value.|
|void ledExcitation() | This function performs led excitation updating shift register values configuration.|
|void updateShiftRegister(uint8_t statusLeds) |Takes as input current led status and performs the new configuration. |

