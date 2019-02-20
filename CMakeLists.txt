CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(axiom_daemon)

include(ExternalProject)

#SET(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
# For faster builds
#SET(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" FORCE)

# If more info about build issues is required
#SET(CMAKE_VERBOSE_MAKEFILE ON)

OPTION(ENABLE_MOCK "Enable mock (e.g. memory-related code) implementation for developemnt" OFF) # Disabled by default
IF(ENABLE_MOCK)
ADD_DEFINITIONS(-DENABLE_MOCK=ON)
ENDIF(ENABLE_MOCK)

# Required by flatbuffers also
ADD_COMPILE_OPTIONS(-std=c++11)

# Make GCC more strict
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Compiler flags
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2") #Optimize
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s") # Strip binary
endif()

# Switched back from fork to original, as GoAPI is not maintained at the moment
# Forked version contains Go generator adjustments for strong types for enums
ExternalProject_Add(flatbuffers_project
    PREFIX ${CMAKE_BINARY_DIR}
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/3rdParty/flatbuffers"
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
    CMAKE_ARGS -DFLATBUFFERS_BUILD_TESTS=OFF -DFLATBUFFERS_INSTALL=OFF -DFLATBUFFERS_BUILD_FLATLIB=OFF -DFLATBUFFERS_BUILD_FLATHASH=OFF)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/3rdParty/flatbuffers/include/)

ExternalProject_Get_Property(flatbuffers_project BINARY_DIR)
SET(FLATC ${BINARY_DIR}/flatc)

# C/C++schema
FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/src/Schema/)
ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_BINARY_DIR}/src/Schema/axiom_daemon_generated.h
    COMMAND ${FLATC} --scoped-enums --gen-object-api --no-prefix --cpp ${PROJECT_SOURCE_DIR}/Schema/axiom_daemon.fbs
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/Schema/
    COMMENT "Running flatc_cpp_gen action"
    DEPENDS flatbuffers_project
    DEPENDS ${CMAKE_SOURCE_DIR}/Schema/axiom_daemon.fbs)

ADD_CUSTOM_TARGET( run_schema_generator DEPENDS ${CMAKE_BINARY_DIR}/src/Schema/axiom_daemon_generated.h
    COMMENT "Checking if re-generation is required" )

FILE(GLOB SOURCE_FILES "Adapter/*.cpp" "Adapter/*.h"
    "Daemon/*.cpp" "Daemon/*.h"
    "Schema/*.fbs"
    "Helpers/*.cpp" "Helpers/*.h"
    "Log/*.cpp" "Log/*.h")

# Copy systemd description files
FILE(COPY "${CMAKE_SOURCE_DIR}/systemd/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
FILE(COPY "${CMAKE_SOURCE_DIR}/Daemon/description.json" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Client example should be build separately for now
ADD_SUBDIRECTORY(API_WS)
ADD_SUBDIRECTORY(CLI)
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/GoAPI/)

# Catch2 (unit test framework)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdParty/)

# Unit tests
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/UnitTests/)

# Used for loading generated headers, e.g. #include <Schema/axiom_daemon_generated.h>
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/src/)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} systemd pthread)

ADD_DEPENDENCIES(${PROJECT_NAME} run_schema_generator)



