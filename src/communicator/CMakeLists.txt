protobuf_generate_grpc_cpp(GRPC_SRCS GRPC_HDRS Communicator.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS Communicator.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(communicator STATIC
        Client.cpp Client.h
        Server.cpp Server.h
        Util.cpp Util.h
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${GRPC_SRCS} ${GRPC_HDRS})

target_link_libraries(communicator ${Protobuf_LIBRARIES})
