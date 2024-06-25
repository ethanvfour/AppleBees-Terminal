cmake_minimum_required(VERSION 3.22.1) # current version when making this project
project(appleBees) # naming project

find_package(Curses REQUIRED)# for n curses?

enable_language(ASM_NASM) # enabling asm for the use of ror and rol

add_library(
    all_users
    allOfUsers/user.h
    allOfUsers/userImp.cpp
    allOfUsers/customerAtLobby.h
    allOfUsers/customerAtLobbyImp.cpp
)#adding all users






#some other libraries if needed that i made
add_library(
    coolFunc
    outsideFunctions/coolFunctions.h
    outsideFunctions/coolFunctionsImp.cpp
)#adding some cool functions


add_executable(appleBees main.cpp outsideFunctions/encrypt.asm)
target_link_libraries(appleBees PRIVATE all_users)
target_link_libraries(appleBees PRIVATE coolFunc)
target_link_libraries(appleBees PRIVATE ${CURSES_LIBRARIES})
