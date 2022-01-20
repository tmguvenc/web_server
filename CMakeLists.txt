cmake_minimum_required(VERSION 3.0)

project(server)

find_package(LibWebSockets REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

execute_process(COMMAND ${Protobuf_PROTOC_EXECUTABLE} -I=${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/rtds.proto)
file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/rtds.pb.h ${CMAKE_CURRENT_SOURCE_DIR}/include/rtds.pb.h)
file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/rtds.pb.cc ${CMAKE_CURRENT_SOURCE_DIR}/src/rtds.pb.cc)

execute_process(COMMAND ${Protobuf_PROTOC_EXECUTABLE} -I=${CMAKE_CURRENT_SOURCE_DIR} --js_out=binary:${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/rtds.proto)
file(GLOB JS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.js")

foreach(js_file ${JS_FILES})
  get_filename_component(barename ${js_file} NAME)
  file(RENAME ${js_file} ${CMAKE_CURRENT_SOURCE_DIR}/mount-origin/${barename})
endforeach(js_file ${JS_FILES})

file(GLOB SOURCE_FILES "src/*.c*")
file(GLOB HEADER_FILES "include/*.h*")

include_directories(include)
include_directories(${Protobuf_INCLUDE_DIR})
include_directories(${LIBWEBSOCKETS_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBWEBSOCKETS_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Protobuf_LIBRARY_RELEASE})