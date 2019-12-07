project(server)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/protobuf-2.5.0/src/)

set(SRC 
    byte_buffer.cc
    byte_buffer.h 
    MsgProtocol.h
)

add_executable(server_test)