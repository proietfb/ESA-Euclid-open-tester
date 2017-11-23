# Spi Commands

This project uses two types of spi Commands: standard and variable; all of these have 32bit size.

## Atomic Commands

### Standard messages

Standard messages are also called atomic commands and are composed by:
- 8 bits that contains das hardware id;
- 8 bits represent hardware component driver;
- 16 bits data to send.

|Name|Spi dev id|Spi Address| Spi Data|
|----|----------|-----------|-------------------|
|LED\_CONF\_1| 0X01 | 36d | 0X8342 |
|LED\_CONF\_2| 0X01 | 37d | 0X8342 |
|LED\_CONF\_3| 0X01 | 38d | 0X302 |
|LED\_CONF\_4| 0X01 | 39d | 0X302 |
|LED\_CONF\_5| 0X01 | 40d | 0X302 |
|LED\_CONF\_6| 0X01 | 41d | 0X302 |
|LED\_CONF\_7| 0X01 | 42d | 0X302 |
|LED\_CONF\_8| 0X01 | 43d | 0X302 |
|LED\_CONF\_9| 0X01 | 15d | 0X8226 |
|LED\_CONF\_10| 0X01 | 4d | 0X0224 |
|LED\_ALL\_DISCONNECT| 0X01 | 71d | 0X8900 |
|LED1\_CONNECT| 0X01 | 71d | 0X0901 |
|LED2\_CONNECT| 0X01 | 71d | 0X0904 |
|LED3\_CONNECT| 0X01 | 71d | 0X0910 |
|LED4\_CONNECT| 0X01 | 71d | 0X0940 |
|LED5\_CONNECT| 0X01 | 71d | 0X0980 |
|HEATER\_CONF1| 0X01 | 13d | 0X0200 |
|HEATER\_CONF2| 0X01 | 14d | 0X8382 |
|MOTOR\_CONF1| 0X01 | 32d | 0X8382 |
|MOTOR\_CONF2| 0X01 | 33d | 0X8382 |
|MOTOR\_CONF3| 0X01 | 34d | 0X100 |
|MOTOR\_CONF4| 0X01 | 35d | 0X100 |
|MOTOR\_CONF5| 0X01 | 53d | 0X3C2 |
|MOTOR\_CONF6| 0X01 | 54d | 0X3C2 |
|MOTOR\_CONF7| 0X01 | 52d | 0X100 |
|MOTOR\_CONF8| 0X01 | 51d | 0X100 |
|MOTOR\_DISCONNECT\_BOTH| 0X01 | 0x47 | 0x0800|
|MOTOR\_CONNECT\_FWA | 0X01 | 0X47 | 0X8801 |
|MOTOR\_CONNECT\_GWA | 0X01 | 0X47 | 0X8804 |
|MOTOR\_SEL\_ENABLE\_CLK1 | 0X01 | 0X40 | 0XE801 |
|MOTOR\_SEL\_ENABLE\_CLK2 | 0X01 | 0X40 | 0X6800 |
|MOTOR\_HS\_DISCONNECT\_BOTH | 0X01 | 0X47 | 0X0D00 |
|MOTOR\_HS\_CONNECT\_FWA | 0X01 | 0X47 | 0X8D04 |
|MOTOR\_HS\_CONNECT\_GWA | 0X01 | 0X47 | 0X8D10 |
|MOTOR\_HS\_POWER\_ON | 0X01 | 0X40 | 0XE701 |
|MOTOR\_HS\_POWER\_OFF | 0X01 | 0X40 | 0X6700 |
|MOTOR\_HS\_RESET\_LATCHES1 | 0X01 | 0X40 | 0X6901 |
|MOTOR\_HS\_RESER\_LATCHES2 | 0X01 | 0X40 | 0XE900 |
|MOTOR\_BRIDGE\_ENABLE | 0X01 | 0X40 | 0XC501 |
|MOTOR\_BRIDGE\_DISABLE | 0X01 | 0X40 | 0X4500 |
|MOTOR\_PROTECTION\_ENABLE | 0X01 | 0X40 | 0XC700 |
|MOTOR\_PROTECTION\_DISABLE | 0X01 | 0X40 | 0X4701 |
|CMD\_MOT\_HS\_READ\_REQ | 0X01 | 0X48 | 0X0000 |

### Variable messages

Variable messages are used to send values from master to slave such as duty cycle, value of current, etc.
All of these messages have the following structure:
- 8 bits: to define device id;
- 8 bits: to set hardware driver;
- 16 bit: to set variable value.

In particular, components which use non standard messages are:
- Heater Driver: to set duty cycle. Max value which can be sent is 0x400.
- Led Driver: to set duty cycle. Max value which can be sent is 1024, where 1/1024 = 0,09765625%.
- Motor Driver: ICU uses this type of messages to send motor current phases. Each motor has two phases and each of them can take a value between -128 and 127. O is equal to 1.64mA.

All data contained on each message is equal to a given start value. For example if phase A of fwa motor is 100, the driver on slave side will increase this value for 1.64 mA and result will be 164.0 mA of current. This method has beeen applied for all messages.


## TM commands

Other than Atomic commands ICU can send messages that represent which telemetry value are requested by master. These messages are 32 bits too and are composed by:
- 3 bits command type: analog, digital, analog/sync, OBT;
- 2 bits settling time register: [0...3];
- 4 bits spi ID;
- 7 bits Spi register Address;
- 16 bits Spi data.

|Name|Command|
|----------------------|------------|
|NI\_SA\_TMP\_1\_CRYO|0X00F78140|
|NI\_SA\_TMP\_2\_CRYO|0X00F70141|
|NI\_SA\_TMP\_3\_CRYO|0X00F70142|
|NI\_SA\_TMP\_4\_CRYO|0X00F78143|
|NI\_SA\_TMP\_5\_CRYO|0X00F70144|
|NI\_SA\_TMP\_6\_CRYO|0X00F78145|
|NI\_CSS\_TMP\_1\_CRYO|0X00F70136|
|NI\_CSS\_TMP\_2\_CRYO|0X00F78137|
|NI\_SSS\_TMP\_1\_CRYO|0X00F70148|
|NI\_SSS\_TMP\_2\_CRYO|0X00F78149|
|NI\_FWA\_TMP\_CRYO|0X00F7812A|
|NI\_GWA\_TMP\_CRYO|0X00F7012B|
|NI\_SA\_TMP\_1\_FR|0X00F78120|
|NI\_SA\_TMP\_2\_FR|0X00F70121|
|NI\_SA\_TMP\_3\_FR|0X00F70122|
|NI\_SA\_TMP\_4\_FR|0X00F78123|
|NI\_SA\_TMP\_5\_FR|0X00F70124|
|NI\_SA\_TMP\_6\_FR|0X00F78125|
|NI\_CSS\_TMP\_1\_FR|0X00F78126|
|NI\_CSS\_TMP\_2\_FR|0X00F70127|
|NI\_SSS\_TMP\_1\_FR|0X00F70128|
|NI\_SSS\_TMP\_2\_FR|0X00F78129|
|NI\_FWA\_TMP\_FR|0X00F7812A|
|NI\_GWA\_TMP\_FR|0X00F7012B|
|FWA\_MOT\_PHA\_I|0X08F7822F|
|FWA\_MOT\_PHB\_I|0X08F7023F|
|GWA\_MOT\_PHA\_I|0X08F7824F|
|GWA\_MOT\_PHB\_I|0X08F7025F|
|NI\_CU\_LED\_V\_1|0X10F7026F|
|NI\_CU\_LED\_V\_2|0X10F7827F|
|NI\_CU\_LED\_V\_3|0X10F7828F|
|NI\_CU\_LED\_V\_4|0X10F7029F|
|NI\_CU\_LED\_V\_5|0X10F702AF|
|ICU\_5V|0X08F782BF|
|ICU\_5V\_CURRENT|0X08F702CF|
|CMD\_MOT\_HS\_READ\_REQ|0X40CA0000|

All TMs commands which ends with \_CRYO are connected with components optimized to acquire cryogenic temperatures. Thermistors from NI\_SA  and NI\_SSS are optimized for range 120-135K.
On the other hand \_FR commands allow full range temperature acquisition 87K-323K. All others TMs acquire values in range of previous declarations.
 

  
 

 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 
 
 
 
 
 



 
