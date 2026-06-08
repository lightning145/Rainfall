cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Rainfall)

add_executable(Rainfall 
        Main.cpp
        World.cpp
        Math.cpp
        Vector.cpp
        Matrix.cpp
        Quaternion.cpp
        Shader.cpp
        Texture.cpp
        glad.c)

set_target_properties(Rainfall PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
)

target_include_directories(Rainfall PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/SDL3-3.4.8/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/
        ${CMAKE_CURRENT_SOURCE_DIR}/KHR/)

target_link_directories(Rainfall PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/SDL3-3.4.8/build/)

target_link_libraries(Rainfall 
        libSDL_uclibc.a
        libSDL3_test.a
        libSDL3.dll.a
)

#if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
 #   target_compile_options(Rainfall PRIVATE 
  #      -O3            
   #     -march=native
    #)
#endif()