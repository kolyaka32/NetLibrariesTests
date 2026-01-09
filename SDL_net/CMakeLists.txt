# Setting cmake requirement for correct compilation
cmake_minimum_required(VERSION 3.10)

# Creating project
project(SDL_net_test)

# Requires C11 standard
set(CMAKE_C_STANDARD 11)

# Add all source files (that needed) under the src directory
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.rc")
add_executable(${PROJECT_NAME} ${SOURCES})

# Linking libraries depending on platform
if (WIN32)
    # Hidding console on windows
    #set(CMAKE_CXX_FLAGS "-mwindows")
endif (WIN32)


# Finding required external libraries
find_package(SDL3 REQUIRED)
find_package(SDL3_net REQUIRED)

# Linking external libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_net::SDL3_net SDL3::SDL3)

