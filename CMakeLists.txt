cmake_minimum_required(VERSION 3.17)
project(CESI_POO)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(SQLAPI_DIR "libs/SQLAPI/")


find_package(Qt5 COMPONENTS Widgets Gui Core OpenGL REQUIRED)
add_executable(${PROJECT_NAME} main.cpp
        utils/DataBase.cpp utils/DataBase.h
        service/StatService.cpp service/StatService.h
        window/main/MainWindow.cpp window/main/MainWindow.h
        assets/resources.qrc model/ModelManager.cpp model/ModelManager.h ihm/IHM.cpp ihm/IHM.h model/StaffModel.cpp model/StaffModel.h model/AddressModel.cpp model/AddressModel.h model/CustomerAddressModel.cpp model/CustomerAddressModel.h model/order/OrderHistoryModel.cpp model/order/OrderHistoryModel.h model/CustomerModel.cpp model/CustomerModel.h model/order/OrderItemModel.cpp model/order/OrderItemModel.h model/order/OrderPaymentModel.cpp model/order/OrderPaymentModel.h model/ItemModel.cpp model/ItemModel.h service/OrderService.cpp service/OrderService.h service/StaffService.cpp service/StaffService.h service/CustomerService.cpp service/CustomerService.h service/ItemService.cpp service/ItemService.h)


target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${SQLAPI_DIR}/include
)

if (WIN32)
    find_library(SQLAPI NAMES sqlapi PATHS ${SQLAPI_DIR}/win32/lib)
elseif (UNIX)
    find_library(SQLAPI NAMES sqlapi PATHS ${SQLAPI_DIR}/unix/lib)
endif ()
target_link_libraries(${PROJECT_NAME} PRIVATE ${SQLAPI})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core Qt5::OpenGL)