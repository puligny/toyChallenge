cmake_minimum_required(VERSION 3.5)

project(toyChallenge)

add_executable(toyChallenge src/main.cpp src/toyrobot.cpp src/instructionhandler.cpp)
target_include_directories(toyChallenge PRIVATE include)


##### TESTS #####
include(CTest)
add_executable(unitTests tests/unittests.cpp
                         tests/toyrobottests.cpp
                         tests/instructionhandlertests.cpp
                         src/toyrobot.cpp
                         src/instructionhandler.cpp)
target_include_directories(unitTests PRIVATE include)
add_test(NAME unitTests COMMAND unitTests)
