# MOTOR DRIVER APIS

Motor driver apis are able to intialize, manage and reset all processes about motors. 

## Motor Driver Master apis

All master side api are located in `~/RaspberryPi/src/fwa_gwa_motor/`. All non void functions if works fine return 0.

|Function Type| Description |
|-------------|-------------|
|uint32\_t initialize()| sends spi CONFx commands to slave|
|uint32\_t reset()| reset motor driver sending disconnect motor and bridge disable messages and setting driver status as "safe"|
|uint32\_t energize(const uint32\_t motor\_id, int8\_t energization\_phase\_a, int8\_t energization\_phase\_b)| this funtion provide motor energization flow. it takes as input, motor id, phase A and phase B energization currents. The flow starts checking if motor driver is on and in this case provide to start deenergization procedure. Then motor bridge is enabled and begin motor connection. Now, first both phases are set on 0 and then new values are sent on driver. Finally selection clock 1 is enabled.|
|uint32\_t execute\_profile(const uint16\_t microstep\_number, const icu\_fwa\_gwa\_microstep_t *p\_microsteps)| This function provide execution profile; it takes as input number of microsted stored on profile and values of microstep. At this point energization and deenergization processes are executed.|
|void stop()| This function stops profile execution.|
|uint32\_t execute\_single\_microstep(const uint32\_t motor\_id, icu\_fwa\_gwa\_microstep\_t *microstep)| takes as input motor id and microstep values and sends them to motor driver using enegization procedure.|
|uint32\_t deenegize()| Deenergize sets all phases to 0, disable driver bridge, disconnect motor and set driver status as disabled.|
|uint32\_t enable\_current\_protection(const bool\_t do\_enable)| If do\_enable is true, this function sends an spi message to enable driver protection.|
|uint32\_t hs\_state\_read(const uint32\_t motor\_id, uint8\_t detection\_threshold, bool\_t *hs\_input\_1, bool\_t *hs\_input\_2)| To read home sensor driver value, this function take as input motor id, detection\_treshold, hs\_input\_1 and hs\_input\_2. First the home sensor driver is connected to motor, and is powered on.|

### Motor Driver profile

Motor Driver execution is provided by loading of Motor profiles All profiles are composed by _n_ steps and each step contains a microstep time (in milliseconds), value of motor phase A and motor phase B. As said in Spi api file, phases can takes values between -128 and 127.

## Motor Driver Slave apis

Apis located on slave device are used to translate icu current phases in values which can perform an BYJ48 stepper motor.

|Function Type | Description |
|--------------|-------------|
|StepperManager()| Costructor of StepperManager class set pin modes as OUTPUT|
|void runMotor(int nSteps) | This function takes as input the number of steps that should be performed. If this value is positive, the motor will do a clockwise round steps, otherwise counterclockwise steps will be performed.|
|void writeStep() | Using digital pin connected, to perform a single motor step, this function write a given pattern of bits.|
|void stepper() | icrease matrix of values which have to be written using digitalWrite() Arduino function.|
|void setDirection()| Depending on nSteps sign increment or decrement step value.|
