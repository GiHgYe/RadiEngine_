cmake_minimum_required(VERSION 3.15)

set(TARGET_NAME SandBox)

file(GLOB_RECURSE SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_executable(${TARGET_NAME} ${SOURCE})

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)


target_link_libraries(${TARGET_NAME} PRIVATE Runtime)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_SOURCE_DIR}/3party/fmod/bin 
        $<TARGET_FILE_DIR:${TARGET_NAME}>
)

