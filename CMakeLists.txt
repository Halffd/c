cmake_minimum_required(VERSION 3.28.1)
project(c C)

# Basic C configuration
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Options
option(GENERATE_ASM "Generate assembly files" OFF)
option(ENABLE_WARNINGS "Enable compiler warnings" ON)

# Find source files
file(GLOB_RECURSE SOURCE_FILES "src/*.c")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Required packages
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
 
# Platform-specific configuration
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
else()
    find_package(Lua REQUIRED)
    if(NOT LUA_FOUND)
        message(FATAL_ERROR "Lua not found!")
    endif()
    
    message(STATUS "Found Lua: ${LUA_VERSION_STRING}")
    message(STATUS "Lua Include Dirs: ${LUA_INCLUDE_DIR}")
    message(STATUS "Lua Libraries: ${LUA_LIBRARIES}")
    
    target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
    #target_link_libraries(${PROJECT_NAME} PRIVATE ${LUA_LIBRARIES} lua)
    target_link_libraries(${PROJECT_NAME} luajit-5.1)
endif()

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    "${CMAKE_SOURCE_DIR}/lib"
)

# Compiler warnings
if(ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE 
            /W4
            /WX
        )
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            #-Werror
        )
    endif()
endif()

# Output configuration
set_target_properties(${PROJECT_NAME} PROPERTIES 
    OUTPUT_NAME ${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

# Assembly generation
if(GENERATE_ASM)
    set(CMAKE_ASM_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/asm")
    file(MAKE_DIRECTORY ${CMAKE_ASM_OUTPUT_DIRECTORY})
    
    foreach(SOURCE_FILE IN LISTS SOURCE_FILES)
        get_filename_component(SOURCE_NAME ${SOURCE_FILE} NAME_WE)
        set(ASM_OUTPUT "${CMAKE_ASM_OUTPUT_DIRECTORY}/${SOURCE_NAME}.s")
        
        add_custom_command(
            OUTPUT ${ASM_OUTPUT}
            COMMAND ${CMAKE_C_COMPILER} 
                -I${CMAKE_SOURCE_DIR}/lib 
                -g 
                -S 
                -O0 
                ${SOURCE_FILE} 
                -o ${ASM_OUTPUT}
            DEPENDS ${SOURCE_FILE}
            COMMENT "Generating assembly for ${SOURCE_NAME}"
        )
        
        add_custom_target(asm_${SOURCE_NAME} 
            ALL 
            DEPENDS ${ASM_OUTPUT}
        )
    endforeach()
endif()