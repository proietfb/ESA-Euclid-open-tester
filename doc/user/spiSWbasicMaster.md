# SPI basic code on Raspberry Pi

Raspberry Pi is equipped with one SPI bus that has 2 chips select. After that master configuration has been enabled (otherwise see [software configuration](../install/installation.md)) there are several ways to connect our devices (Alternative methods are [here](https://www.raspberrypi.org/documentation/hardware/raspberrypi/spi/README.md)). 
Using spidev kernel module Raspberry allow us to open a virtual file conventional named as SPI hardware interface.
```c++
fd = open("/dev/spidev0.0", O_RDWR);
```
`spidevX.Y` is hardware interface that we used to establish an SPI communication. Raspberry Pi can enable two chip select and communicates with two parallel slave devices; if you connect more than two devices using Raspberry Pi as master you have to configure them using daisy-chain configuration.
In our case we open `spidev0.0` because we enabled chip 0 (Y) and used *spidev0* (spidevX) that is only SPI interface on RPI. `O_RDWR` permit to have a read/write access on file.

Now to pass information to and from SPI hardware we have to configure session options using *ioctl*.
Here we should set all session properties that we have talked on [SPI protocol overview](./spiProtocol.md), including SPI mode for polarity, clock phase, bit width, bit wise (MSB or LSB), and so on. Some of these are default on Raspberry Pi and our session is the following: SPI mode is 0, 8 bits per word and each word is sent and received using most significant bit mode. 
Atmel [reference](http://www.atmel.com/Images/Atmel-2585-Setup-and-Use-of-the-SPI_ApplicationNote_AVR151.pdf) for SPI define that system clock for slave device should be at least 4 times the tran	smission SPI rate. Arduino Uno is an ATMEGA328P with 8Mhz of frequency and speed clock from Raspberry Pi could be max 2Mhz. Here we set speed as 1Mhz through ioctl system call.
```c++
unsigned int speed = 1000000;
ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
```
After that we have defined all settings, we want send and receive data. To do this is necessary create a structure allowed by *ioctl* and allocate space for a transfer and a receive buffer.
```c++
unsigned char txBuff;
unsigned char rxBuff;

struct spi_ioc_transfer spi;
memset(&spi,0,sizeof(spi));
spi.tx_buf = (unsigned long) &txDat;
spi.rx_buf = (unsigned long) &rxDat;
spi.len = 1; 
```
`spi` structure takes as attributes two buffers and a variable `len` that define number of transmissions. `memset()` simply allocate memory for struct.

To send words we perform:
```c++
ioc(fd, SPI_IOC_MESSAGE(1),&spi);
```
Here through ioctl system call we pass spi struct data that will be sent to the virtual file. This operation involves also that *rxDat* buffer will be filled with incoming data from MISO line.

Below there is full basic Raspberry Pi code:

```c++
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int fd; // SPI  device
int ret; //used to control SPI communication errors
unsigned char val; //input to send
unsigned char  result; //receive 'buffer'

static void pabort(const char *s); // SPI error checker
int spiTxRx(unsigned char txDat); //send and receive data from slave

int main(void){

	fd = open("/dev/spidev0.0",O_RDWR);//open SPI device communication
	if (fd < 0){
		pabort("Can't open SPI device");
	}

	unsigned int speed = 1000000;

	ret = ioctl(fd,SPI_IOC_WR_MAX_SPEED_HZ,&speed);//set communication speed

	if (ret < 0)
		pabort("can't send using this speed");
	cout<<"Value to send: "<<endl;
	cin>> val;

	//Send and print received data

	result=spiTxRx(val);
	cout<<result<<endl;
	close(fd);
}

static void pabort(const char *s){
	perror(s);
	abort();
}

int spiTxRx(unsigned char txDat){
	unsigned char rxDat;
	struct spi_ioc_transfer spi;
	memset(&spi,0,sizeof(spi));
	spi.tx_buf = (unsigned long) &txDat; //send buffer
	spi.rx_buf = (unsigned long) &rxDat; //receive buffer
	spi.len = 1; //data length

	ret = ioctl (fd, SPI_IOC_MESSAGE(1), &spi);
	if (ret < 1)
		pabort("can't send SPI message");

	return rxDat;
}

```

## References
- [Atmel AVR](http://www.atmel.com/Images/Atmel-2585-Setup-and-Use-of-the-SPI_ApplicationNote_AVR151.pdf);
- [Sparkfun doc](https://learn.sparkfun.com/tutorials/raspberry-pi-spi-and-i2c-tutorial#spi-on-pi);
- [spidev doc](https://www.kernel.org/doc/Documentation/spi/spidev);
- [Raspduino](http://robotics.hobbizine.com/raspiduino.html).


go back to [summary](../summary.md).
