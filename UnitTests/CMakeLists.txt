CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(DaemonTests)

SET(CMAKE_VERBOSE_MAKEFILE, ON)
  
# Required by flatbuffers also
ADD_COMPILE_OPTIONS(-std=c++11)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/..)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../3rdParty/)

# Used for loading generated headers, e.g. #include <Schema/axiom_daemon_generated.h>
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/src/)

FILE(GLOB SOURCE_FILES "*.cpp" "*.h"
                       "../Adapter/*.cpp" "../Adapter/*.h"
                       "../API_WS/MessageHandler.cpp" "../API_WS/MessageHandler.h")

list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../API_WS/Main.cpp")

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
ADD_DEPENDENCIES(${PROJECT_NAME} axiom_daemon)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} systemd)
