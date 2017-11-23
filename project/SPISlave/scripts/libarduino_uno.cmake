
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
enable_language(ASM)

set(EXECUTABLE_OUTPUT_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/lib/")
set(LIBRARY_OUTPUT_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/lib/")

# C only fine tunning
set(TUNNING_FLAGS "-funsigned-char -funsigned-bitfields -fpack-struct") 

set(CMAKE_CXX_FLAGS "-mmcu=${ARDUINO_UNO_MCU} -DF_CPU=${ARDUINO_UNO_FCPU} -Os -std=gnu++11 -static-libstdc++")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${TUNNING_FLAGS} -Wall -Wstrict-prototypes -std=gnu99")

set(ARDUINO_UNO_INSTALLED_LIBS "$ENV{HOME}Arduino/libraries/")
set(ARDUINO_UNO_CORE_DIR "${ARDUINO_UNO_ROOT}/hardware/avr/1.6.17/")
set(ARDUINO_UNO_PINS_DIR "${ARDUINO_UNO_ROOT}/hardware/avr/1.6.17/variants/${ARDUINO_UNO_BOARD}")
set(ARDUINO_UNO_PINS_DIR "${ARDUINO_UNO_ROOT}/hardware/avr/1.6.17/variants/${ARDUINO_UNO_BOARD}")
set(ARDUINO_UNO_AVR_DIR "${ARDUINO_UNO_ROOT}/tools/avrdude/6.3.0-arduino8/include")
set(AVRDUDE_CONFIG "${ARDUINO_UNO_ROOT}/tools/avrdude/6.3.0-arduino8/etc/avrdude.conf")

include_directories(${ARDUINO_UNO_PINS_DIR})
include_directories(${ARDUINO_UNO_CORE_DIR}/cores/arduino/)
include_directories(${ARDUINO_UNO_AVR_DIR})

set(ARDUINO_UNO_SOURCE_FILES
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/wiring_pulse.S
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/wiring_digital.c
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/wiring.c
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/WInterrupts.c
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/wiring_pulse.c
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/wiring_shift.c
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/hooks.c 
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/wiring_analog.c
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/WMath.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/IPAddress.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/Tone.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/HardwareSerial2.cpp
	${ARDUINO_UNO_CORE_DIR}/libraries/HID/src/HID.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/Print.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/new.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/HardwareSerial0.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/HardwareSerial.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/WString.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/abi.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/USBCore.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/Stream.cpp
	${ARDUINO_UNO_CORE_DIR}/cores/arduino/CDC.cpp
)

add_library(core STATIC ${ARDUINO_UNO_SOURCE_FILES})


set(PORT $ENV{ARDUINO_UNO_PORT})
if (NOT PORT)
    set(PORT ${ARDUINO_UNO_PORT})
endif()

add_custom_target(reset_uno)
add_custom_command(TARGET reset POST_BUILD
    COMMAND echo 0 > ${PORT}
)

macro(arduino TARGET_NAME TARGET_SOURCE_FILES)

  add_library(${TARGET_NAME} STATIC ${ARDUINO_UNO_CORE_DIR}/cores/arduino/main.cpp ${SOURCE_FILES})
  
  add_custom_target(${TARGET_NAME}.elf)
  add_dependencies(${TARGET_NAME}.elf core ${TARGET_NAME})
	
  add_custom_command(TARGET ${TARGET_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_CXX_COMPILER} -w -Os -Wl,--gc-sections -mmcu=atmega328p -o ${LIBRARY_OUTPUT_PATH}/${TARGET_NAME}.elf -lm ${LIBRARY_OUTPUT_PATH}/lib${TARGET_NAME}.a -lm ${LIBRARY_OUTPUT_PATH}/libcore.a
  )
  

  add_custom_target(${TARGET_NAME}.hex)
  add_dependencies(${TARGET_NAME}.hex ${TARGET_NAME}.elf)

  add_custom_command(TARGET ${TARGET_NAME}.hex POST_BUILD
      COMMAND ${ARDUINO_UNO_OBJCOPY} -O ihex -R .eeprom ${LIBRARY_OUTPUT_PATH}/${TARGET_NAME}.elf ${LIBRARY_OUTPUT_PATH}/${TARGET_NAME}.hex
  )
  
  add_custom_target(${TARGET_NAME}.upload)
  add_dependencies(${TARGET_NAME}.upload ${TARGET_NAME}.hex)

  add_custom_command(TARGET ${TARGET_NAME}.upload POST_BUILD
      COMMAND ${ARDUINO_UNO_AVRDUDE} -C${AVRDUDE_CONFIG} -v -p${ARDUINO_UNO_MCU} -c${ARDUINO_UNO_PROTOCOL}  -P${PORT} -b${ARDUINO_UNO_UPLOAD_SPEED} -D -Uflash:w:${LIBRARY_OUTPUT_PATH}/${TARGET_NAME}.hex:i
  )
  
  add_custom_target(${TARGET_NAME}.clean)
  add_custom_command(TARGET ${TARGET_NAME}.clean POST_BUILD
      COMMAND rm -rf ${CMAKE_SOURCE_DIR}/build/* && rm -rf ${CMAKE_SOURCE_DIR}/lib
  )

  add_custom_target(${TARGET_NAME}.monitor)
  add_custom_command(TARGET ${TARGET_NAME}.monitor POST_BUILD
      COMMAND xfce4-terminal -T Serial_Monitor -e 'screen ${ARDUINO_UNO_PORT}'
  )
endmacro()

