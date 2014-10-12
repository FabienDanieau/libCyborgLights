Project(CyborgLigths)
cmake_minimum_required(VERSION 2.6)


set(EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})
set(LIB_NAME libCybordLights)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake_modules)

FIND_PACKAGE(libusb-1.0 REQUIRED)

IF(NOT LIBUSB_1_FOUND)
  MESSAGE(FATAL_ERROR "libusb-1.0 is required to build CyborgLights.")
ENDIF(NOT LIBUSB_1_FOUND)

INCLUDE_DIRECTORIES(${LIBUSB_1_INCLUDE_DIRS})

ADD_LIBRARY(
	${LIB_NAME}
	SHARED
        ../src/constants.h
	../src/cyborgLights.cpp
)

TARGET_LINK_LIBRARIES(
    ${LIB_NAME}
    ${LIBUSB_1_LIBRARIES}
)

set(EXE_NAME testLights)

ADD_EXECUTABLE(
    ${EXE_NAME}
    ../src/main.cpp
)

TARGET_LINK_LIBRARIES(
    ${EXE_NAME}
    ${LIB_NAME}
)
