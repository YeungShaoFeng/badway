cmake_minimum_required(VERSION 2.4)

project(badway)


# detecting the current operating system
MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    # Fix the libgcc_s_dw2-1.dll issue
    set(CMAKE_EXE_LINKER_FLAGS -static)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    MESSAGE(STATUS "current platform: FreeBSD")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

MESSAGE(STATUS "###################################")

set(CMAKE_CXX_STANDARD 14)
# 
#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
# fix "'nullptr' was not declared in this scope"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_executable(
        badway
        src/main.cpp
        src/sha256.c
        src/mylib.cpp
)

include_directories(
        openssl
        include
        PI
)

add_compile_options(-Wno-nullability-completeness)
