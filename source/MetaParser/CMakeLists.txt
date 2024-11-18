cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(TARGET_NAME MetaParser)

add_executable(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/parser 
    ${CMAKE_CURRENT_SOURCE_DIR}/3party/clang/include
    ${CMAKE_CURRENT_SOURCE_DIR}/3party/mustache/include
)

find_library(CLANG_LIBRARY libclang.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/3party/clang/lib)

target_link_libraries(${TARGET_NAME} ${CLANG_LIBRARY})

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/3party/clang/bin 
    $<TARGET_FILE_DIR:${TARGET_NAME}>
)
