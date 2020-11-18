cmake_minimum_required(VERSION 3.17.3)
project(CESI_POO)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Gui Core OpenGL REQUIRED)

add_executable(CESI_POO main.cpp
        model/history/HistoryOrder.cpp model/history/HistoryOrder.h
        model/Customer.cpp model/Customer.h
        model/Staff.cpp model/Staff.h
        model/Item.cpp model/Item.h
        utils/DataBase.cpp utils/DataBase.h
        utils/Statistiques.cpp utils/Statistiques.h
        window/main/MainWindow.cpp window/main/MainWindow.h
        window/content/TabManager.cpp window/content/TabManager.h
        window/content/StaffTab.cpp window/content/StaffTab.h
        window/content/OrderTab.cpp window/content/OrderTab.h
        assets/resources.qrc)

target_link_libraries(CESI_POO PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core Qt5::OpenGL)