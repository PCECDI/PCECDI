cmake_minimum_required(VERSION 3.5)

set(ProjectName PCECDI)
project(${ProjectName} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PCECDI_TS_Files
    Translations/PCECDI_fr.ts
    Translations/PCECDI_ru.ts
    Translations/PCECDI_de.ts
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network LinguistTools Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network LinguistTools Xml)

set(PROJECT_SOURCES
        main.cpp
        MainUI.h
        SettingsUI.h
        XmlReader.h
	Ressources/Ressources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${ProjectName}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${ProjectName} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${ProjectName}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${ProjectName} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Xml)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.PCECDI.${ProjectName})
endif()
set_target_properties(${ProjectName} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set_source_files_properties(
    ${PCECDI_TS_Files}
    PROPERTIES OUTPUT_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/translations"
)

qt_add_translations(PCECDI TS_FILES ${PCECDI_TS_Files})

include(GNUInstallDirs)
install(TARGETS ${ProjectName}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${ProjectName})
endif()
