cmake_minimum_required(VERSION 3.14.6)

# CMake version
message(STATUS "CMake Ver: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION}")

###############################################################################
# Device Check
###############################################################################
# Platform & Processor
set(HOST_ARCH "")
if (UNIX)
    execute_process(COMMAND uname -m OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE HOST_ARCH) # OUTPUT_STRIP_TRAILING_WHITESPACE : 改行を省く
    if(${HOST_ARCH} STREQUAL "")
        execute_process(COMMAND uname -p OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE HOST_ARCH)
    endif()
    if(${HOST_ARCH} STREQUAL "")
        message(FATAL_ERROR "Not found architecture symbol in Unix.")
    endif()
endif()

if(WIN32)
    message(STATUS "Platform: Windows ${CMAKE_SYSTEM_VERSION}")
    set(HOST_ARCH $ENV{PROCESSOR_ARCHITECTURE})
    if(${HOST_ARCH} STREQUAL "")
        message(FATAL_ERROR "Not found architecture symbol in Windows.")
    endif()
elseif(UNIX AND NOT APPLE)
    message(STATUS "Platform: Linux ${CMAKE_SYSTEM_VERSION}")
elseif(APPLE)
    message(STATUS "Platform: macOS ${CMAKE_SYSTEM_VERSION}")
else()
    message(FATAL_ERROR "Platform: Not match platforms [Windows, macOS, Linux]. Given platform is ${CMAKE_SYSTEM_NAME}")
endif()

if(APPLE)
    set(OSX_ARCHITECTURE "")
    if(${HOST_ARCH} MATCHES "arm64")
        list(APPEND OSX_ARCHITECTURE "AppleSilicon")
    elseif(${HOST_ARCH} MATCHES "x86_64")
        list(APPEND OSX_ARCHITECTURE "Intel(Rosetta2)")
    else()
        message(FATAL_ERROR "Not match architecture. Arch must arm64 or x86_64 in macOS. Given is ${ARCH}")
    endif()
    message(STATUS "Your macOS cpu architecture is ${HOST_ARCH} ${OSX_ARCHITECTURE}!")
endif()
message(STATUS "Host arch: ${HOST_ARCH}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}") # コンパイル対象のプロセッサ
message(STATUS "CMAKE_HOST_SYSTEM_PROCESSOR: ${CMAKE_HOST_SYSTEM_PROCESSOR}") # 実行しているプロセッサ

# Generator
# https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html
message(STATUS "Generator: ${CMAKE_GENERATOR}")

###############################################################################
# Top-level Project Name
###############################################################################
project(RTTI LANGUAGES CXX VERSION 0.1.0)

###############################################################################
# Core
###############################################################################
include(./is_test_case.cmake)

# Include dir
include_directories(./Rtti)
include_directories(./Interface)
include_directories(./MonoInheritedEntity) 
include_directories(./MultiInheritedEntity)
include_directories(./Factory)

#Headers
file(GLOB RTTI_HEADERS RELATIVE ./Rtti ./*.hpp) # Rtti
file(GLOB INTERFACE_HEADERS RELATIVE ./Interface ./*.hpp) # Interface
file(GLOB ENTITY_HEADERS RELATIVE ./MonoInheritedEntity ./*.hpp) # Mono Inherited Entities
file(GLOB FACTORY_HEADERS RELATIVE ./Factory ./*.hpp) # Factory

set(BUILD_HEADERS "")
list(APPEND BUILD_HEADERS ${RTTI_HEADERS})
list(APPEND BUILD_HEADERS ${INTERFACE_HEADERS})
list(APPEND BUILD_HEADERS ${ENTITY_HEADERS})
list(APPEND BUILD_HEADERS ${FACTORY_HEADERS})

# Sources
file(GLOB RTTI_SOURCES RELATIVE ./Rtti ./*.cpp) # Rtti
file(GLOB INTERFACE_SOURCES RELATIVE ./Interface ./*.cpp) # Interface
file(GLOB ENTITY_SOURCES RELATIVE ./MonoInheritedEntity ./*.cpp) # Mono Inherited Entities
file(GLOB FACTORY_SOURCES RELATIVE ./Factory ./*.cpp) # Factory

set(BUILD_SOURCES "")
list(APPEND BUILD_SOURCES ${RTTI_SOURCES})
list(APPEND BUILD_SOURCES ${INTERFACE_SOURCES})
list(APPEND BUILD_SOURCES ${ENTITY_SOURCES})
list(APPEND BUILD_SOURCES ${FACTORY_SOURCES})

# Mono RTTI System 
make_is_test_case("${BUILD_HEADERS}" "${BUILD_SOURCES}" ./mono_rtti_system.cpp)

file(GLOB MULTI_ENTITY_HEADERS RELATIVE ./MultiInheritedEntity ./*.hpp)
file(GLOB MULTI_ENTITY_SOURCES RELATIVE ./MultiInheritedEntity ./*.cpp) # Multi Inherited Entities

list(APPEND BUILD_HEADERS ${MULTI_ENTITY_HEADERS})
list(APPEND BUILD_SOURCES ${MULTI_ENTITY_SOURCES})

# Multi RTTI System
make_is_test_case("${BUILD_HEADERS}" "${BUILD_SOURCES}" ./multi_rtti_system.cpp)