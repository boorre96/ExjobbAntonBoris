cmake_minimum_required(VERSION 3.13.1)

project(client C)

# Set path to nanopb library
set(NANOPB_DIR "$ENV{HOME}/Thesis/my-workspace/modules/lib/nanopb")

# Set path to generated protobuf files
set(PROTOBUF_DIR "$ENV{HOME}/Thesis/my-workspace/ExjobbAntonBoris/app/src")

# Include nanopb headers
include_directories(${NANOPB_DIR})

# Add nanopb source code
set(NANOPB_SRC
    ${NANOPB_DIR}/pb_common.c
    ${NANOPB_DIR}/pb_decode.c
    ${NANOPB_DIR}/pb_encode.c
)

# Add nanopb library
add_library(nanopb STATIC ${NANOPB_SRC})

# Generate protobuf files
find_program(PROTOC protoc)
add_custom_command(
  OUTPUT ${PROTOBUF_DIR}/simple.pb.c ${PROTOBUF_DIR}/simple.pb.h
  COMMAND ${PROTOC} --proto_path=${PROTOBUF_DIR}
          --plugin=protoc-gen-nanopb=${NANOPB_DIR}/generator/protoc-gen-nanopb
          --nanopb_out=${PROTOBUF_DIR} ${PROTOBUF_DIR}/simple.proto
  DEPENDS ${PROTOBUF_DIR}/simple.proto
)

# Add client executable
add_executable(client client.c ${PROTOBUF_DIR}/simple.pb.c)
target_include_directories(client PUBLIC ${PROTOBUF_DIR})
target_link_libraries(client PRIVATE nanopb)