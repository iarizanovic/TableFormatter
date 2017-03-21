cmake_minimum_required(VERSION 2.6)
project(tableformatter)
add_definitions(-std=c++11)
add_executable(tableformatter main.cpp TableFormatterBase.cc TableCell.cc)

install(TARGETS tableformatter RUNTIME DESTINATION bin)
