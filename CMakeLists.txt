cmake_minimum_required(VERSION 3.1)
project(concu_lucas_fede_tp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)
set(FIFOS src/Util/Fifos/Fifo.cpp src/Util/Fifos/Fifo.h src/Util/Fifos/FifoEscritura.cpp src/Util/Fifos/FifoEscritura.h src/Util/Fifos/FifoLectura.cpp src/Util/Fifos/FifoLectura.h)
set(SHARED_MEMORY src/Util/MemoriaCompartida/MemoriaCompartida.h)
set(LOCK_FILE src/Util/Locks/LockFile.h src/Util/Locks/LockFile.cpp)
set(SEMAPHORE src/Util/Semaforo/Semaforo.h src/Util/Semaforo/Semaforo.cpp)
set(SIGNALS src/Util/Seniales/EventHandler.h src/Util/Seniales/SIGINT_Handler.h src/Util/Seniales/SignalHandler.cpp src/Util/Seniales/SignalHandler.h)

add_executable(ConcuTP ${SOURCE_FILES} ${FIFOS} ${SHARED_MEMORY} ${LOCK_FILE} ${SIGNALS} ${SEMAPHORE} src/Util/Pipes/Pipe.cpp src/Util/Pipes/Pipe.h src/Util/INIReader/ini.h src/Util/INIReader/ini.c src/Util/INIReader/INIReader.h src/Util/INIReader/INIReader.cpp src/Config/Config.h src/Util/Locks/LockFile.h src/Util/Locks/LockFile.cpp src/Util/Cola/Cola.h src/Util/Logger/Logger.h src/Util/Logger/Logger.cpp src/Util/MixedUtils.cpp src/Util/MixedUtils.h src/Domain/Process/Process.h src/Domain/Process/Process.cpp src/Domain/Client/Client.h src/Domain/Client/Client.cpp src/Domain/DatabaseManager/DatabaseManager.h src/Domain/DatabaseManager/DatabaseManager.cpp src/Domain/EntryRow/entryRow.h src/Domain/Persona/Persona.cpp src/Domain/Persona/Persona.h src/Exception/InvalidParamsException.cpp src/Exception/InvalidParamsException.h)