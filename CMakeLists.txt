cmake_minimum_required(VERSION 3.17.3)
project(CESI_POO)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(CESI_POO main.cpp manager/window/WindowManager.cpp
        manager/window/WindowManager.h
        manager/window/WindowManager.ui model/history/HistoryOrder.cpp model/history/HistoryOrder.h model/Customer.cpp model/Customer.h model/Staff.cpp model/Staff.h model/Item.cpp model/Item.h utils/DataBase.cpp utils/DataBase.h utils/Statistiques.cpp utils/Statistiques.h)
target_link_libraries(CESI_POO PRIVATE Qt5::Widgets)