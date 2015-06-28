cmake_minimum_required(VERSION 3.1)
project(concu_lucas_fede_tp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)
set(SIGNALS src/Util/Seniales/EventHandler.h src/Util/Seniales/SIGINT_Handler.h src/Util/Seniales/SignalHandler.cpp src/Util/Seniales/SignalHandler.h)

add_executable(ConcuTP ${SOURCE_FILES} ${SIGNALS} src/Util/INIReader/ini.h src/Util/INIReader/ini.c src/Util/INIReader/INIReader.h src/Util/INIReader/INIReader.cpp src/Config/Config.h src/Util/Locks/LockFile.h src/Util/Locks/LockFile.cpp src/Util/Cola/Cola.h src/Util/Logger/Logger.h src/Util/Logger/Logger.cpp src/Util/MixedUtils.cpp src/Util/MixedUtils.h src/Domain/Process/Process.h src/Domain/Process/Process.cpp src/Domain/Client/Client.h src/Domain/Client/Client.cpp src/Domain/DatabaseManager/DatabaseManager.h src/Domain/DatabaseManager/DatabaseManager.cpp src/Domain/EntryRow/entryRow.h src/Domain/Persona/Persona.cpp src/Domain/Persona/Persona.h src/Exception/InvalidParamsException.cpp src/Exception/InvalidParamsException.h src/Exception/MessageQueueException.cpp src/Exception/MessageQueueException.h)