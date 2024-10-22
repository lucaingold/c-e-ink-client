cmake_minimum_required(VERSION 3.29)
project(c_e_ink_client C)

set(CMAKE_C_STANDARD 17)

# Specify the directory where IT8951 source files are located
set(IT8951_SRC_DIR "IT8951")
set(LIBS_SOURCE_DIR "libs")
file(GLOB IT8951_SRC "${IT8951_SRC_DIR}/*.c")

# Ensure the minimum CMake version for find_package
cmake_minimum_required(VERSION 3.5)
find_package(eclipse-paho-mqtt-c REQUIRED)

# Create the executable
add_executable(c_e_ink_client main.c)

# Link the necessary libraries for the executable
target_link_libraries(c_e_ink_client eclipse-paho-mqtt-c::paho-mqtt3as)

# Detect if compiling on a Raspberry Pi (using /proc/cpuinfo)
if(EXISTS "/proc/cpuinfo" AND IS_DIRECTORY "/opt/vc")
    message(STATUS "Compiling on Raspberry Pi")

    # Include the IT8951 directory and add its source files
    include_directories("${IT8951_SRC_DIR}")
    target_sources(c_e_ink_client PRIVATE ${IT8951_SRC})

    # Find and link BCM2835 library (only on Raspberry Pi)
    find_library(BCM2835_LIB bcm2835)
    if(BCM2835_LIB)
        target_link_libraries(c_e_ink_client ${BCM2835_LIB})
    else()
        message(FATAL_ERROR "BCM2835 library not found!")
    endif()
else()
    message(STATUS "Not on Raspberry Pi")
endif()
