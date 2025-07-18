cmake_minimum_required(VERSION 3.16) 

project(ORbitImgui VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard 20")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${SRC_DIR}/**.cpp")
file(GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS "${INCLUDE_DIR}/**.h")

add_library(ORbitImgui STATIC)
add_library(gfx::Imgui ALIAS ORbitImgui)

target_sources(ORbitImgui
    PRIVATE
    ${INCLUDE_FILES}
    ${SRC_FILES}
)

target_include_directories(ORbitImgui
    PUBLIC
    ${INCLUDE_DIR}
)