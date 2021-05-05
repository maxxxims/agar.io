cmake_minimum_required(VERSION 3.19)
project(Agario_v2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Agario_v2 main.cpp start_menu.h start_menu.cpp start_menu.h constances.h field.cpp field.h PlayerInterface.h traps.cpp traps.h point.cpp point.h Player.cpp Player.h bot.cpp bot.h)