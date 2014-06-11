# Create a library called "qabel".

file(GLOB SOURCE_FILES "*.cpp" "messages/*.cpp" "config/*.cpp" "chat/*.cpp" "net/*.cpp" "digest/*.cpp" "crypto/*.cpp" "hmac/*.cpp" "fs/*.cpp" "block/*.cpp" "encoding/*.cpp" "ffsync/*.cpp")
file(GLOB HEADER_FILES "*.h" "messages/*.h" "config/*.h" "chat/*.h" "net/*.h" "digest/*.h" "crypto/*.h" "hmac/*.h" "fs/*.h" "block/*.h" "encoding/*.h" "ffsync/*.h")

include_directories(.)
include_directories(chat)
include_directories(config)
include_directories(crypto)
include_directories(digest)
include_directories(hmac)
include_directories(messages)
include_directories(net)
include_directories(fs)
include_directories(encoding)
include_directories(block)
include_directories(ffsync)

# Creating shared/static builds with different names. See
# stackoverflow.com/questions/2152077/is-it-possible-to-get-cmake-to-build-both-a-static-and-shared-version-of-the-sam
# for the reason
add_library (qabel_static STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries (qabel_static ${LIBS})
add_library (qabel SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries (qabel -lresolv)
target_link_libraries (qabel ${LIBS})
