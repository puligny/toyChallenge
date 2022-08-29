cmake_minimum_required(VERSION 3.5)

project(toyChallenge)

add_executable(toyChallenge src/main.cpp src/toyrobot.cpp)

target_include_directories(toyChallenge PRIVATE include)
