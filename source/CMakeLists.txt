cmake_minimum_required(VERSION 2.8)
message(STATUS "***************************************************************************************")

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules")

message(STATUS "CMAKE_MODULE_PATH = " "${CMAKE_MODULE_PATH}")

find_package(GDBM)

if (GDBM_FOUND)
        message(STATUS "Found GDBM installation!")
        message(STATUS "GDBM_INCLUDE_DIR = " "${GDBM_INCLUDE_DIR}")
        message(STATUS "GDBM_LIBRARIES   = " "${GDBM_LIBRARIES}")
        include_directories(${GDBM_INCLUDE_DIR})
    	add_executable(gdbm2dump gdbm2dump.cpp)
        target_link_libraries(gdbm2dump ${GDBM_LIBRARIES})
else (GDBM_FOUND)
        message(WARNING "GDBM installation not found")
endif (GDBM_FOUND)

add_executable(helo helo.cpp)

message(STATUS "***************************************************************************************")
