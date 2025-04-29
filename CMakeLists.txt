# Require the CMake version matching what is included in the latest LTS version
# of Ubuntu, which at the time of writing is 22.04.
cmake_minimum_required(VERSION 3.22)

# file(READ "./pico_sdk_path.txt" PICO_PATH)

set(ENV{PICO_SDK_PATH} "/home/esun/Documents/SoftSys/pico-sdk/")

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

# TODO: Define a good project in the line below. If applicable, list other
# languages in this project managed by CMake.
project(Whack-A-Mole C CXX ASM)

# Initialize the SDK
pico_sdk_init()
set(PICO_BOARD pico)

# pico_find_compiler(PICO_COMPILER_LD ${PICO_GCC_TRIPLE}-ld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# Include the source files.
add_subdirectory(src)
# Include pimoroni keypad library
add_subdirectory(rgb_keybad_lib)

# Use the latest C standard supported by Clang and LLVM in the latest LTS
# version of Ubuntu.
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wdouble-promotion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wduplicated-branches")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wduplicated-cond")
# The following line is only needed in LLVM/clang
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wimplicit-fallthrough")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wlogical-op")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmisleading-indentation")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wnull-dereference")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshadow")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wsign-conversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunreachable-code")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunused")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# No options are set here because the configuration is set in .clang-tidy
# instead. If that file is not present, clang-tidy will be of limited help.
set(CMAKE_C_CLANG_TIDY "clang-tidy")

# In current courses that teach C, we use the Criterion testing framework. If
# If you want to use a different framework, or if you want to skip testing
# entirely (not recommended), change the lines below.
include(CTest)
find_library(CRITERION criterion PATHS /usr/lib/x86_64-linux-gnu REQUIRED)
set(CRITERION_FLAGS --verbose -j1)

add_subdirectory(test)
