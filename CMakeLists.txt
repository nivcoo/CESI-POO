cmake_minimum_required(VERSION 3.17.3)
project(CESI_POO)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:\\Programmes\\Qt\\5.15.0\\mingw81_64\\lib\\cmake")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_executable(CESI_POO main.cpp manager/window/WindowManager.cpp
        manager/window/WindowManager.h
        manager/window/WindowManager.ui)
target_link_libraries(CESI_POO PRIVATE Qt5::Widgets)