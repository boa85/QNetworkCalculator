cmake_minimum_required(VERSION 3.7)
project(QNetworkCalculator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O0 -pedantic-errors -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Wno-ignored-qualifiers -Wno-unused-parameter")
set(CMAKE_PREFIX_PATH "/opt/soft/qt/5.8/gcc_64/")#указать путь к  Qt
set(CMAKE_AUTOMOC ON)#Q_OBJECT - для использования в проекте механизма сигналов и слотов.
find_package(Qt5Core REQUIRED)# по аналогии с *.pro QT += gui core
find_package( Qt5Widgets REQUIRED )#виджеты
find_package( Qt5Network REQUIRED )#Сеть

set(SOURCE_FILES main.cpp gui/src/main_window.cpp
        gui/include/main_window.h
        gui/src/calc_widget.cpp
        gui/include/calc_widget.h
        gui/src/settings_dialog.cpp
        gui/include/settings_dialog.h
        network/src/tcp_socket.cpp
        network/include/tcp_socket.h service/include/service.hpp)
add_executable(QNetworkCalculator ${SOURCE_FILES})
target_link_libraries(QNetworkCalculator Qt5::Widgets Qt5::Core Qt5::Network )# с которыми будем линковать бинарник