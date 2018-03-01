protobuf_generate_grpc_cpp(GRPC_SRCS GRPC_HDRS Communicator.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS Communicator.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(communicator STATIC
        Client.cpp Client.h
        ComputationServer.cpp ComputationServer.h
        Util.cpp Util.h
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${GRPC_SRCS} ${GRPC_HDRS})

add_executable(server-exec serverMain.cpp)
add_executable(client-exec ../../tests/communicator/clientMain.cpp)

target_link_libraries(communicator ${Protobuf_LIBRARIES})
target_link_libraries(server-exec communicator executor platform neuralnet netbuilder protobuf grpc grpc++)
target_link_libraries(client-exec communicator executor platform neuralnet netbuilder protobuf grpc grpc++)