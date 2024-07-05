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
    allOfUsers/customerAtTable.h
    allOfUsers/customerAtTableImp.cpp
)#adding all users

add_library(
    all_items
    allOfUsers/otherObj/table.h 
    allOfUsers/otherObj/tableImp.cpp
    allOfUsers/otherObj/Item.h
    allOfUsers/otherObj/ItemImp.cpp
)





#some other libraries if needed that i made
add_library(
    coolFunc
    outsideFunctions/coolFunctions.h
    outsideFunctions/coolFunctionsImp.cpp
)#adding some cool functions

add_executable(testy test.cpp)
target_link_libraries(testy PRIVATE ${CURSES_LIBRARIES})

add_executable(appleBees main.cpp outsideFunctions/encrypt.asm)
target_link_libraries(appleBees PRIVATE all_users)
target_link_libraries(appleBees PRIVATE coolFunc)
target_link_libraries(appleBees PRIVATE ${CURSES_LIBRARIES})
target_link_libraries(appleBees PRIVATE all_items)