cmake_minimum_required(VERSION 3.5)

project(y2mate VERSION 2.2.5 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/images/appicon.rc")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        resources.qrc
        main.cpp

        searchvideowindow.cpp
        searchvideowindow.h
        searchvideowindow.ui

        settingsdialog.h
        settingsdialog.cpp
        settingsdialog.ui

        downloadvideowindow.h
        downloadvideowindow.cpp
        downloadvideowindow.ui

        downloaddialog.h
        downloaddialog.cpp
        downloaddialog.ui

        editvideodialog.h
        editvideodialog.cpp
        editvideodialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(y2mate
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${APP_ICON_RESOURCE_WINDOWS}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET y2mate APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(y2mate SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(y2mate
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(y2mate PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(y2mate PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS y2mate
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(y2mate)
endif()

find_package(Qt6 REQUIRED COMPONENTS Network)
target_link_libraries(y2mate PRIVATE Qt6::Network)

find_package(Qt6 REQUIRED COMPONENTS Core5Compat)
target_link_libraries(y2mate PRIVATE Qt6::Core5Compat)

find_package(Qt6 REQUIRED COMPONENTS Multimedia)
target_link_libraries(y2mate PRIVATE Qt6::Multimedia)
