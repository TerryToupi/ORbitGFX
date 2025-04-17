cmake_minimum_required(VERSION 3.16) 

project(ORbitGFX VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard 20")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(EXTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/external/)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${SRC}/**.cpp")
file(GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS "${INCLUDE}/**.hpp")

# DAWN 
set(TINT_BUILD_SPV_READER ON) 
set(TINT_BUILD_WGSL_READER ON) 
set(TINT_BUILD_SPV_WRITER ON) 
set(TINT_BUILD_WGSL_WRITER ON) 
add_subdirectory(${EXTERNAL}/dawn) 

# shaderc
set(SHADERC_SKIP_TESTS ON) 
set(SHADERC_SKIP_EXAMPLES ON) 
set(SHADERC_ENABLE_SHARED_CRT ON)
add_subdirectory(${EXTERNAL}/shaderc)

add_library(ORbitGFX STATIC)
add_library(gfx::ORbit ALIAS ORbitGFX)

target_sources(ORbitGFX
    PRIVATE
    ${INCLUDE_FILES}
    ${SRC_FILES}
)

target_include_directories(ORbitGFX
    PUBLIC
    "${INCLUDE}/renderer"
    "${INCLUDE}/utilities"
    PRIVATE
    "${INCLUDE}/platform"
)

target_link_libraries(ORbitGFX
    PRIVATE
    dawn::webgpu_dawn
    dawn::dawn_glfw 
    glfw 
    shaderc
    libtint
)

# POST BUILD ACTIONS 
#######################################################################################################
function(copy_target_files target)
    # Function to copy the output file of a dependency target next to the target executable
    # Arguments:
    #   target: The primary target to which the command will be attached
    #   dependency: The target whose output file will be copied

    add_custom_command(
        TARGET "${target}" POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:webgpu_dawn> $<TARGET_FILE_DIR:${target}>
    )
endfunction()
