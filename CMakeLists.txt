cmake_minimum_required(VERSION 3.17)
project(CESI_POO)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


if (WIN32)
    set(SQLAPI_DIR "libs/SQLAPI/win32")
elseif (UNIX)
    set(SQLAPI_DIR "libs/SQLAPI/unix")
endif ()


find_package(Qt5 COMPONENTS Widgets Gui Core OpenGL REQUIRED)
add_executable(${PROJECT_NAME} main.cpp
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
        assets/resources.qrc model/ModelManager.cpp model/ModelManager.h ihm/IHM.cpp ihm/IHM.h)


target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${SQLAPI_DIR}/include
)


find_library(SQLAPI NAMES sqlapi PATHS ${SQLAPI_DIR}/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SQLAPI})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core Qt5::OpenGL)