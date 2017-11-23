# Software side configuration for SPI protocol

Here we talk about the software side basic environment set up.

## RaspberryPi

This project was developed on the raspberryPi B+ and tested using Raspbian Jessie image downloaded from official [website](https://www.raspberrypi.org/downloads/raspbian/).
Flashed image, you should make sure that SPI communication is enabled. Hence, from terminal type ```$ sudo raspi-config```, goes to _interfacing options_, _SSH_, and confirm submitting _YES_ option.
Now you need to be sure that all drivers are enabled: type `$ lsmod` and check if *spi_bcm2835* and *spidev* modules are loaded; Otherwise type ```$ modprobe pi_bcm2835``` and/or `$ modprobe spidev`.
The code is written in C++ and compiled using the GNU Compiler Collection. Gcc is a part of Raspbian distro (currently is 4.9.2 version), so you can compile code using  ```$ g++ -o [target] [source]```. To use SPI peripheral we need root permissions: you can execute code typing `$ sudo ./example`. 

## Arduino
Arduino is an open-source platform able to manage several end-devices as LEDS, motors, sensors, etc. Arduino use a C/C++ microcontroller libraries and also an IDE desktop is available from official [website](https://www.arduino.cc/en/Guide/HomePage).


Go back to [summary](../summary.md)
