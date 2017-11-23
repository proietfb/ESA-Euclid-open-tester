set(LIBS ./libs/)
set(DHT ${LIBS}DHT/)

set(SOURCE_FILES
    SPISlave.cpp
    heaterManager.cpp
    shiftRegManager.cpp
    spiSlaveManager.cpp
    StepperManager.cpp
    tempSens.cpp
    TMManager.cpp
    HsManager.cpp
    ${LIBS}array.hpp
    ${DHT}dht.cpp
    
)
include_directories(./)
include_directories(${LIBS})
include_directories(${DHT})

arduino(SPISlave ${SOURCE_FILES})

