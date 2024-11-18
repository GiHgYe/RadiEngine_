cmake_minimum_required(VERSION 3.15)

set(TARGET_NAME Runtime)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${TARGET_NAME} STATIC ${SOURCES})

file(GLOB HANDERS ${CMAKE_SOURCE_DIR}/3party/*/include)

target_include_directories(${TARGET_NAME} PUBLIC include;
    ${CMAKE_SOURCE_DIR}/source/MetaGenerate;
    ${HANDERS};
)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

find_library(FMOD_CORE_LIBRARY fmodL_vc.lib ${CMAKE_SOURCE_DIR}/3party/fmod/lib)
find_library(FMOD_STUDIO_LIBRARY fmodstudioL_vc.lib ${CMAKE_SOURCE_DIR}/3party/fmod/lib)

target_link_libraries(${TARGET_NAME} PUBLIC
    glfw freetype spdlog::spdlog luasocket yaml-cpp lua sol2 ${FMOD_CORE_LIBRARY} ${FMOD_STUDIO_LIBRARY} 
)

target_compile_options(${TARGET_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/bigobj>)
target_compile_definitions(${TARGET_NAME} PRIVATE NOMINMAX)