# Setting cmake requirement for correct compilation
cmake_minimum_required(VERSION 3.10)

# Creating project
project(winSockTest)

# Requires C11 standard
set(CMAKE_C_STANDARD 11)

# Add all source files (that needed) under the src directory
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.rc")
add_executable(${PROJECT_NAME} ${SOURCES})

# Linking libraries depending on platform
if (WIN32)
    # Hidding console on windows
    #set(CMAKE_CXX_FLAGS "-mwindows")
    # Linking library for net
    target_link_libraries(${PROJECT_NAME} PRIVATE wsock32 iphlpapi)
endif (WIN32)


# Finding required external libraries
#find_package( REQUIRED)

# Linking external libraries
#target_link_libraries(${PROJECT_NAME} PRIVATE )
