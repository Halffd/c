cmake_minimum_required(VERSION 3.28.1)
project(c C)

set(CMAKE_C_STANDARD 11)              # Set the C standard to C11
set(CMAKE_C_STANDARD_REQUIRED ON)     # Make the standard required
set(CMAKE_C_EXTENSIONS OFF)           # Disable compiler-specific extensions

# Create a boolean option for assembly generation
option(GENERATE_ASM "Generate assembly files" ON)

file(GLOB_RECURSE source_files "src/*.c")

add_executable(c ${source_files})

# Find the necessary packages if needed (for example, pthread for multi-threading)
find_package(Threads REQUIRED)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    set(SOCKETS "Ws2_32.lib") # Link against Winsock
    target_link_libraries(c ${CMAKE_THREAD_LIBS_INIT} ws2_32)
else()
    #find_package(PkgConfig REQUIRED)
    #pkg_check_modules(LUA REQUIRED lua)
    #include_directories(${LUA_INCLUDE_DIRS})
    #target_link_libraries(c ${LUA_LIBRARIES})
    # Non-Windows settings (e.g., for Linux or macOS)
    #find_package(Lua REQUIRED)  # Find Lua package
    #include_directories(${LUA_INCLUDE_DIR})  # Include Lua headers
    #target_link_libraries(c ${CMAKE_THREAD_LIBS_INIT} ${LUA_LIBRARIES})  # Link Lua libraries
    # Specify paths to Lua
endif()

# Include directories for your lib
include_directories("${CMAKE_SOURCE_DIR}/lib")

# Enable all warnings for GCC and Clang
target_compile_options(c PRIVATE
        #-Wall        # Enable all warnings
        #-Wextra     # Enable extra warnings
        #-Wpedantic   # Enable strict ISO C/C++ compliance
        #-Werror      # Treat warnings as errors
)

# Set output properties 
set_target_properties(c PROPERTIES OUTPUT_NAME c)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Set the output directory for the assembly files
set(CMAKE_ASM_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/asm)

# Ensure the output directory exists
file(MAKE_DIRECTORY ${CMAKE_ASM_OUTPUT_DIRECTORY})

# Loop through source files to generate assembly if the option is enabled
if(GENERATE_ASM)
    foreach(source_file IN LISTS source_files)
        get_filename_component(source_name ${source_file} NAME_WE)
        add_custom_command(
            OUTPUT ${CMAKE_ASM_OUTPUT_DIRECTORY}/${source_name}.s  # Assembly output file
            COMMAND ${CMAKE_C_COMPILER} -I${CMAKE_SOURCE_DIR}/lib -g -S -O0 ${source_file} -o ${CMAKE_ASM_OUTPUT_DIRECTORY}/${source_name}.s
            DEPENDS ${source_file}
            COMMENT "Generating assembly for ${source_file}"
        )
        add_custom_target(generate_asm_${source_name} ALL DEPENDS ${CMAKE_ASM_OUTPUT_DIRECTORY}/${source_name}.s)
    endforeach()
endif()