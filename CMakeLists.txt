cmake_minimum_required(VERSION 3.5)

project(Library VERSION 0.1 LANGUAGES CXX)

# debugging macros
add_compile_definitions(
    #DEBUG_ON
    #_ADD_DEBUG_CONSOLE
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:\\installed\\lib\\Qt\\6.6.0\\msvc2019_64" CACHE PATH "")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS 
    Widgets 
    Core 
    Gui 
    Pdf 
    PdfWidgets
)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS 
    Widgets 
    Core 
    Gui 
    Pdf 
    PdfWidgets
)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    debug.h
    paths.h
    

    custom_widgets/patterntab/patterntab.h
    custom_widgets/patterntab/patterntab.cpp
    custom_widgets/patternview/patternview.h
    custom_widgets/patternview/patternview.cpp
    custom_widgets/exampletab/exampletab.h
    custom_widgets/exampletab/exampletab.cpp
    custom_widgets/source_code_view/sourcecodeview.h
    custom_widgets/source_code_view/sourcecodeview.cpp

    models/pattern/pattern.h
    models/pattern/pattern.cpp
    models/pattern/code_examples/codeexamples.h
    models/pattern/code_examples/codeexamples.cpp
    models/pattern/code_examples/example.h
    models/pattern/code_examples/example.cpp

    models/library/Library.h
    models/library/Library.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Library
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Library APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Library SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Library
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(
    Library PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Pdf
    Qt${QT_VERSION_MAJOR}::PdfWidgets
)

set_target_properties(Library PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Library
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Library)
endif()
