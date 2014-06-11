# Create the "libqabel" project.

cmake_minimum_required (VERSION 2.8)
project (libqabel)
add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Glib)
include_directories(${Glib_INCLUDE_DIRS})
list(APPEND LIBS ${Glib_LIBRARIES})

find_package(ZLIB)
include_directories(${ZLIB_INCLUDE_DIRS})
list(APPEND LIBS ${ZLIB_LIBRARIES})

find_package(Jsonc)
include_directories(${Jsonc_INCLUDE_DIRS})
list(APPEND LIBS ${Jsonc_LIBRARIES})

find_package(OpenSSL)
include_directories(${OPENSSL_INCLUDE_DIR})
list(APPEND LIBS ${OPENSSL_LIBRARIES})

find_package(CURL)
include_directories(${CURL_INCLUDE_DIR})
list(APPEND LIBS ${CURL_LIBRARIES})

find_package(ZLIB)
include_directories(${ZLIB_INCLUDE_DIR})
list(APPEND LIBS ${ZLIB_LIBRARIES})

include_directories(include src src/chat src/block src/fs)

add_subdirectory (src)
add_subdirectory (examples)
