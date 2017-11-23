# Heater Driver

There are two heaters: FPA and SA. In this project both heaters are simulated with two PWM LEDs. 

## Heater Driver Master Apis

All functions in `heaterDriver.h` and perform control and access to led driver located in das board. All non-void functions return 0 if do not report errors.

|Function prototypes| Description |
|-------------------|-------------|
|uint32\_t initialize()| This function send spi commands to config both heaters.|
|uint32\_t switch\_on(uint8\_t identifier, uint16\_t duty\_cycle\_in\_ticks) | This function sends an spi command to perform an heater switch on sending identify value and duty cycle in ticks.|
|uint32\_t switch\_off(uint8\_t identifier) | Using spi protocol send duty cycle equal to 0 to switch off a given heater.|
|uint32\_t reset() | reset all heaters.|

#Heater Driver Slave Apis

`HeaterManager.h` contains all functions to manage heaters connected with das driver.

|Function prototypes| Description |
|-------------------|-------------|
| void spiDataHeaters(uint16\_t address, uint16\_t data) | This function takes address and data as input and process a given spi command.|
|void heaterInitialize() | Initizalize heater driver setting `ledPin_` as OUTPUT and performing an analog write with a given `configValue_`.|
|void setHeater(uint16\_t setValue) | If initialized, this function set heater value; convert ICU value in das value and performs an analog write.|
|void reset() | reset heater driver.|
