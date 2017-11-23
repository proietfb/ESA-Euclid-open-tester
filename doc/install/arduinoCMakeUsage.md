# Compile Arduino projects using CMAKE

Arduino IDE is a nice and useful environment for beginners, but when you are doing large software projects it becomes unwidely; to avoid this, a strong solution is build your project with CMAKE. In this section we will talk about CMAKE and how to configure it to compile and upload Arduino skethes. Moreover we are going to set up a serial monitor to read Arduino responses.

## Why CMAKE?

CMAKE is an open-source build manager for software projects that allows developers to specify build parameters in a simple text files format. This files are used from CMAKE to build native tools to handle all difficults of a cross-platform software.

## Basic CMAKE usage

The build process is controlled by creating one or more `CMakeLists.txt` files in each project directory. All these files are filled by comments (that starting with `#`) and commands using `command(args...)` systax. `command` is a name of command and `args` consists in one or more arguments listed with a white-space separation. `args` can be listed in severl ways:
```cmake
command("") # 1 quoted argument
command("a b c") # 1 quoted argument
command(a b c) # 3 unquoted arguments
command(a; b; c) # 1 unquote argument exoanded to 3
```
CMake also support variables. A simple method to store a string is using `set()`; the sintax is `set(FOO value)` where `FOO` is variable name and `value` is value string. The syntax to reference a variable in a command is `${FOO}`. To access to system environment variables use `$ENV{VAR}` where `VAR` is variable name.

### HelloWorld for CMAKE

To copile an executable from one source file, the unique CMakeLists will contain the following two lines:
```cmake
project(Hello)
add_executable(Hello hello.cpp)
```

`project()` indicates what the name of the resulting workspace should be and `add_executable()`, add an executable target to the build process.

## Compiling sketches for Arduino Uno

After this very short tutorial to this language let start our Arduino Uno builder.

### Package install and check

To compile skecthes we need to install or check some packages:
- Arduino Uno IDE (currently is 1.8.1 version). It provide to install all packages needed to compile and upload firmwares.
- Install lastest version of CMake from your package manager or downloading it from [official website](https://cmake.org/download/).
- Screen package to allow Arduino serial monitor.
- check versions of:
	- `avr-gcc`
	- `avr-g++`
	- `avr-objcopy`
	- `avrdude`

`avr-gcc` and `avr-g++` are simply GNU compiler for c and cpp files, `avr-objcopy` copy the contents of object file to another and `avrdude` is a driver program for download code and data to Atmel AVR microcontrollers. For many details see corrispetively man pages

### Project Tree

As said before we have to add a `CMakeLists.txt` on every project folder structure will be:
```
SPISlave/
   |
   -- src/
   |	|
   |	-- SPISlave/
   |	|	|
   |    |	-- Source files and libs used
   |	|	|
   |	|	-- CMakeLists.txt
   |	-- CMakeLists.txt
   -- scripts/
   |	|
   |	-- arduino_uno.cmake
   |	|
   |	-- libarduino_uno.cmake
   |
   -- CMakeLists.txt
```
### CMAKEs building files

Starting from `SPISlave` folder we have CMakeLists.txt that contains project name, minimum version required (currently is CMake 3.7 but deep changes was been made from v2.6). `set` is a variable which sets verbose outputs during project building, `include` command loads and run CMake code from a file or module (`${CMAKE_SOURCE_DIR}` is a variable setted by default after `project` command).`add_subdirectory` adds a subdirectory to the build; the value of this last command cpecifies the directory in which the source CMakeLists.txt and code files are located (look that value is a relative path that starts from root project folder).
```cmake
project(SPISlave)
cmake_minimum_required(VERSION 2.6)
set( CMAKE_VERBOSE_MAKEFILE on )

include(${CMAKE_SOURCE_DIR}/scripts/arduino_uno.cmake)

add_subdirectory(src)
```
On `src` directory CMakeLists.txt simply adds `SPISlave` subdirectory that contains all source files and `libs` folder with external libraries. Cmake text on `SPISlave` is:
```cmake
set(SOURCE_FILES
    SPISlave.cpp
    heaterManager.cpp
    shiftRegManager.cpp
    spiSlaveManager.cpp
    StepperManager.cpp
    tempSens.cpp
    libs/Stepper.cpp
    libs/Stepper.h
)
include_directories(./)
include_directories(./libs/)

arduino(SPISlave ${SOURCE_FILES})
```
Here we set all source file in these directories included and then we call `arduino()` macro locate on `libarduino_uno.cmake` passing target name and target source files.

Finally in `scripts` folder we have CMake code that contains all options to compile and upload Arduino projects.
`arduino_uno.cmake` is included by CMakeLists.txt on the root project folder and contains all options related Arduino Uno board (such as processor, upload speed, protocol and root home folder), serial port where Arduino is connected, and all tools to compile and upload project files. 

```cmake
set(ARDUINO_UNO_PROTOCOL "arduino")
set(ARDUINO_UNO_BOARD "standard")
set(ARDUINO_UNO_MCU "atmega328p")
set(ARDUINO_UNO_FCPU "16000000")
set(ARDUINO_UNO_UPLOAD_SPEED "115200")
set(ARDUINO_UNO_PORT "/dev/ttyACM0")
set(ARDUINO_UNO_ROOT "$ENV{HOME}.arduino15/packages/arduino")
set(CMAKE_C_COMPILER "${ARDUINO_UNO_ROOT}/tools/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-gcc")
set(CMAKE_CXX_COMPILER "${ARDUINO_UNO_ROOT}/tools/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++")
set(ARDUINO_UNO_OBJCOPY "${ARDUINO_UNO_ROOT}/tools/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-objcopy")
set(ARDUINO_UNO_AVRDUDE "${ARDUINO_UNO_ROOT}/tools/avrdude/6.3.0-arduino8/bin/avrdude")
include(${CMAKE_SOURCE_DIR}/scripts/libarduino_uno.cmake)
```

Last line of `arduino_uno.cmake` includes `libarduino_uno.cmake` file where are listed all rules to compile and upload our projects.

About this file instead of list all code we'll talk about main components:

```cmake
set(TUNNING_FLAGS "-funsigned-char -funsigned-bitfields -fpack-struct")
```
On this variable are setted gcc tunning flags: 
- `-f unsigned-char` set chars as unsigned as default;
- `-f unsigned-bitfields` when unspecified set bitfield as unsigned;
- `-f pack-struct` pack all structure members without holes;

```cmake
set(CMAKE_CXX_FLAGS "-mmcu=${ARDUINO_UNO_MCU} -DF_CPU=${ARDUINO_UNO_FCPU} -Os -std=gnu++11")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${TUNNING_FLAGS} -Wall -std=gnu99")
```
C++ flags compile takes avr microcontroller board (`-mmcu= `), and CPU frequency of Arduino. `-Os` is a code optimization level and `-std=gnu++11` determine the standard language.
C flags other than C++ options enable all output warnings (`Wall`) and C99 standard.

The code after compiler flags declare where gcc compilers and Arduino core libraries are located, then `add_library(core STATIC ${ARDUINO_UNO_SOURCE_FILES})` import them as static libraries.

```cmake
macro(arduino TARGET_NAME TARGET_SOURCE_FILES)

  add_library(${TARGET_NAME} STATIC ${ARDUINO_UNO_CORE_DIR}/cores/arduino/main.cpp ${SOURCE_FILES})
  
  add_custom_target(${TARGET_NAME}.elf)
  add_dependencies(${TARGET_NAME}.elf core ${TARGET_NAME})
  
  # On terminal with `make TARGET_NAME.elf` we will compile our source file 

  add_custom_command(TARGET ${TARGET_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_CXX_COMPILER} -w -Os -Wl,--gc-sections -mmcu=atmega328p -o ${LIBRARY_OUTPUT_PATH}/${TARGET_NAME}.elf -lm ${LIBRARY_OUTPUT_PATH}/lib${TARGET_NAME}.a -lm ${LIBRARY_OUTPUT_PATH}/libcore.a
  )
  
  # here with `make TARGET_NAME.hex` we will perform an object copy
	
  add_custom_target(${TARGET_NAME}.hex)
  add_dependencies(${TARGET_NAME}.hex ${TARGET_NAME}.elf)

  add_custom_command(TARGET ${TARGET_NAME}.hex POST_BUILD
      COMMAND ${ARDUINO_UNO_OBJCOPY} -O ihex -R .eeprom ${LIBRARY_OUTPUT_PATH}/${TARGET_NAME}.elf ${LIBRARY_OUTPUT_PATH}/${TARGET_NAME}.hex
  )
  
  # `make TARGET_NAME.upload` upload firmware on board using ATMEL driver

  add_custom_target(${TARGET_NAME}.upload)
  add_dependencies(${TARGET_NAME}.upload ${TARGET_NAME}.hex)

  add_custom_command(TARGET ${TARGET_NAME}.upload POST_BUILD
      COMMAND ${ARDUINO_UNO_AVRDUDE} -C${AVRDUDE_CONFIG} -v -p${ARDUINO_UNO_MCU} -c${ARDUINO_UNO_PROTOCOL}  -P${PORT} -b${ARDUINO_UNO_UPLOAD_SPEED} -D -Uflash:w:${LIBRARY_OUTPUT_PATH}/${TARGET_NAME}.hex:i
  )
  
  # `make TARGET_NAME.clean` performs a simply `make clean`
  
  add_custom_target(${TARGET_NAME}.clean)
  add_custom_command(TARGET ${TARGET_NAME}.clean POST_BUILD
      COMMAND rm -rf ${CMAKE_SOURCE_DIR}/build/* && rm -rf ${CMAKE_SOURCE_DIR}/lib
  )
  
  # `make TARGET_NAME.monitor open screen serial monitor on new virtual Konsole terminal

  add_custom_target(${TARGET_NAME}.monitor)
  add_custom_command(TARGET ${TARGET_NAME}.monitor POST_BUILD
      COMMAND konsole -T Serial_Monitor -e 'screen ${ARDUINO_UNO_PORT}'
  )
endmacro()
```

A CMAKE macro records instructions which are invoked when macro was been invoked too. Macro's arguments are `<name>` and `args...` some optional arguments. 
Inside `arduino` macro we add core main cpp and our source files  as libraries. Then we initialize some custom commands that can be invoked from terminal after initial build. 


## Usage

After checked if all path are rights, from terminal got to project root directory and performs following commands:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```
If you want clean project type `make target_name.clean`, to upload use `make target_name.upload` command and with `make target_name.monitor` a new konsole window will be opened with a monitor which listen on Arduino serial port.

## Arduino Uno serial Monitor

There are several ways to open a serial monitor, one of these is to use `screen` package. Screen is a full-screen window manager that multiplexes a physical terminal between several processes (typically interactive shells). With `make target_name.monitor` `screen konsole -T Serial_Monitor -e 'screen ${ARDUINO_UNO_PORT}` command will be performed and `${ARDUINO_UNO_PORT}` is /dev/ttyACM0.
N.B To close screen window you have to type `control-a``shift-k` and then yes. If you close window screen will remain attached and serial port will result busy; in this case typing `screen -list` you can see which monitors are actives and kill them using `kill` command.

Go back to [summary](../summary.md).

## References

- Mastering CMAKE 3.1, Ken Martin, Bill Hoffman. Kitware.
- CMAKE documentation [page](https://cmake.org/cmake/help/v3.7/)
- [Arduino-Cmake-template](https://github.com/maxbader/Arduino-CMake-Template) git repository
- gcc man page
- screen man page


