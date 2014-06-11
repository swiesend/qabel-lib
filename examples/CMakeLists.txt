# Create some example programs.

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/config)
include_directories(${PROJECT_SOURCE_DIR}/src/messages)
include_directories(${PROJECT_SOURCE_DIR}/src/block)
include_directories(${PROJECT_SOURCE_DIR}/src/fs)
include_directories(${PROJECT_SOURCE_DIR}/src/net)

add_executable(messages messages.cpp)
target_link_libraries (messages qabel)

add_executable(qbl qbl.cpp)
target_link_libraries (qbl qabel)

add_executable(json_read json_read.cpp)
target_link_libraries (json_read qabel)

add_executable(block block.cpp)
target_link_libraries (block qabel)
