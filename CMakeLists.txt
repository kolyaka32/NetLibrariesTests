cmake_minimum_required(VERSION 3.15)
project(winSockTest)

set(CMAKE_C_STANDARD 11) # Requires C11 standard

# Add all source files (that needed) under the src directory
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.rc")
add_executable(${PROJECT_NAME} ${SOURCES})

# Hidding console on windows
if (WIN32)
    #set(CMAKE_CXX_FLAGS "-mwindows")
    target_link_libraries(${PROJECT_NAME} PRIVATE wsock32)
endif (WIN32)


# Executable & linking
#find_package(raylib REQUIRED)

#target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
