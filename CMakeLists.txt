cmake_minimum_required(VERSION 3.5)

set(ProjectName PCECDI_v2)
project(${ProjectName} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        MainUI.h
        SettingsUI.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${ProjectName}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Ressources/Ressources.qrc
    )
endif()

target_link_libraries(${ProjectName} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(${ProjectName} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${ProjectName})
endif()
