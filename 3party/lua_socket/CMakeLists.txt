cmake_minimum_required(VERSION 3.15)
set(TARGET_NAME luasocket)

file(GLOB SOURCES "src/*.c")

add_library(${TARGET_NAME} STATIC ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC include ${CMAKE_SOURCE_DIR}/3party/lua/include)

add_dependencies(${TARGET_NAME} lua)

# target_link_libraries(${TARGET_NAME} PUBLIC lua)
target_link_libraries(${TARGET_NAME} PRIVATE ws2_32)
