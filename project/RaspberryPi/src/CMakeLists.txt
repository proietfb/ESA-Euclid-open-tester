set(SPI_DRIVER ${CMAKE_SOURCE_DIR}/src/spi_driver/)
set(HEATER_DRIVER ${CMAKE_SOURCE_DIR}/src/heater_driver/)
set(LED_DRIVER ${CMAKE_SOURCE_DIR}/src/led_driver/)
set(MOTOR_DRIVER ${CMAKE_SOURCE_DIR}/src/fwa_gwa_motor/)
set(TM_ACQ ${CMAKE_SOURCE_DIR}/src/tm_acq_manager/)

set(SOURCE_FILES_LIB
	${SPI_DRIVER}spi_driver.cpp
	${SPI_DRIVER}spi_drv.cpp
	${HEATER_DRIVER}heater_driver.cpp
	${HEATER_DRIVER}heater_drv.cpp
	${LED_DRIVER}led_drivers.cpp
	${LED_DRIVER}led_drv.cpp
	${MOTOR_DRIVER}fwa_gwa_motor_drivers.cpp
	${MOTOR_DRIVER}fwa_gwa_motor_drv.cpp
	${TM_ACQ}tm_acq_manager.cpp
	${TM_ACQ}tm_acq_mng.cpp
	
)
set(SOURCE_HEADER_LIB
	${SPI_DRIVER}spi_driver.h
	${SPI_DRIVER}spi_drv.h
	${HEATER_DRIVER}heater_driver.h
	${HEATER_DRIVER}heater_drv.h
	${LED_DRIVER}led_drivers.h
	${LED_DRIVER}led_drv.h
	${MOTOR_DRIVER}fwa_gwa_motor_drivers.h
	${MOTOR_DRIVER}fwa_gwa_motor_drv.h
	${TM_ACQ}tm_acq_manager.h
	${TM_ACQ}tm_acq_mng.h
)

add_library(raspi_lib SHARED ${SOURCE_FILES_LIB} ${SOURCE_HEADER_LIB})

set(CMAKE_C_FLAGS "-I${SPI_DRIVER} -I${HEATER_DRIVER} -I${LED_DRIVER} -I${MOTOR_DRIVER} -I${TM_ACQ}")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -I${SPI_DRIVER} -I${HEATER_DRIVER} -I${LED_DRIVER} -I${MOTOR_DRIVER} -I${TM_ACQ}")

add_executable(Demo demo.c)

target_link_libraries(Demo raspi_lib)

add_executable(RaspberryPic masterMain.c)

target_link_libraries(RaspberryPic raspi_lib)
