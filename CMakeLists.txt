# Setting cmake requirement for correct compilation
cmake_minimum_required(VERSION 3.10)

# Creating main project
project(NetLibs)

# Add sub directories
# SDL_net library
add_subdirectory(SDL_net)
# Winsock2 library
add_subdirectory(WinSock2)
# Winsock2 library
#add_subdirectory(WinSockTest)
