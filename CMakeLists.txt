cmake_minimum_required(VERSION 3.15)

project(
    Engine
    LANGUAGES CXX C
    VERSION 1.0.0
)

add_subdirectory(source/SandBox)
add_subdirectory(source/Runtime)
add_subdirectory(source/MetaParser)
add_subdirectory(3party/glfw)
add_subdirectory(3party/spdlog)
add_subdirectory(3party/yaml-cpp)
add_subdirectory(3party/lua)
add_subdirectory(3party/lua_socket)
add_subdirectory(3party/sol)
add_subdirectory(3party/freetype)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB HANDERS ${CMAKE_SOURCE_DIR}/3party/*/include ${CMAKE_SOURCE_DIR}/source/*/include)
set(HANDERS ${CMAKE_SOURCE_DIR}/source/MetaGenerate;${HANDERS})

set(PRECOMPILE_PARSER ${CMAKE_SOURCE_DIR}/build/source/MetaParser/Debug/MetaParser.exe)
set(CODEGEN_TARGET "PreCompile")

add_custom_target(${CODEGEN_TARGET} ALL
    COMMAND ${CMAKE_COMMAND} -E echo "----------------------------"
    COMMAND ${CMAKE_COMMAND} -E echo "--  Pre-compiling begin  --"
    COMMAND ${CMAKE_COMMAND} -E echo "----------------------------"
    COMMAND ${PRECOMPILE_PARSER} 
        ${CMAKE_SOURCE_DIR}/source 
        ${CMAKE_SOURCE_DIR}/source/MetaGenerate/precompile_header.h 
        "${HANDERS}";
        * 1
)
add_dependencies(${CODEGEN_TARGET} MetaParser)
add_dependencies(Runtime ${CODEGEN_TARGET})



# 生成 .clangd 配置文件
# set(CLANGD_CONFIG_FILE ${CMAKE_SOURCE_DIR}/.clangd)
# file(WRITE ${CLANGD_CONFIG_FILE} "CompileFlags:\n  Add: [\n")
# foreach(HANDLER ${HANDERS})
#     file(APPEND ${CLANGD_CONFIG_FILE} "    \"-I${HANDLER}\",\n")
# endforeach(HANDLER ${HANDERS})
# file(APPEND ${CLANGD_CONFIG_FILE} "  ]\n")
