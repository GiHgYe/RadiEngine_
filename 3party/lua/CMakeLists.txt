cmake_minimum_required(VERSION 3.15)
set(TARGET_NAME lua)

file(GLOB SOURCE src/*.c)

add_library(${TARGET_NAME} STATIC ${SOURCE})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# target_compile_features(${TARGET_NAME} PRIVATE c_std_99)
