cmake_minimum_required(VERSION 3.0)

project(server)

find_package(LibWebSockets REQUIRED)
find_package(Boost REQUIRED)
file(GLOB SOURCE_FILES "src/*.c*")
file(GLOB HEADER_FILES "include/*.h*")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${LIBWEBSOCKETS_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBWEBSOCKETS_LIBRARIES})
target_link_libraries(${PROJECT_NAME} boost_serialization)