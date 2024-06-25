cmake_minimum_required(VERSION 3.22.1) # current version when making this project
project(appleBees) # naming project

find_package(Curses REQUIRED)# for n curses?

enable_language(ASM_NASM) # enabling asm for the use of ror and rol

add_library(
    user_imp
    allOfUsers/user.h
    allOfUsers/userImp.cpp
)#adding user parent class

add_library(
    customerLobby
    allOfUsers/customerAtLobby.h
    allOfUsers/customerAtLobbyImp.cpp
)#adding child class customerAtLobby





#some other libraries if needed that i made
add_library(
    coolFunc
    outsideFunctions/coolFunctions.h
    outsideFunctions/coolFunctionsImp.cpp
)#adding some cool functions




add_executable(appleBees main.cpp encrypt.asm)
target_link_libraries(appleBees PRIVATE user_imp)
target_link_libraries(appleBees PRIVATE customerLobby)
target_link_libraries(appleBees PRIVATE coolFunc)
target_link_libraries(appleBees PRIVATE ${CURSES_LIBRARIES})
