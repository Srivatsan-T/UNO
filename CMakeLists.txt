cmake_minimum_required(VERSION 3.5)

project(Uno-2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(QT_USE_QTMULTIMEDIA TRUE)
SET(QT_USE_QTMULTIMEDIAWIDGETS TRUE)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

include_directories(libraries/include/SDL2)
link_directories(libraries/lib)

set(PROJECT_SOURCES
        main.cpp
        greeting.cpp
        greeting.h
        greeting.ui
        rules.h
        rules.cpp
        rules.ui
        inputs.cpp
        inputs.h
        inputs.ui
        card.cpp
        card.h
        users.cpp
        users.h
        server_greeting.cpp
        server_greeting.h
        server_greeting.ui
        client_greeting.cpp
        client_greeting.h
        client_greeting.ui
        game.cpp
        game.h
        profiledata.txt
        profilemanager.cpp
        profilemanager.h
        profilemanager.ui
        bot_player.cpp
        bot_player.h
        soundclass.cpp
        soundclass.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Uno-2
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Uno-2 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Uno-2
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(Uno-2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets   -mwindows  mingw32 SDL2main  SDL2  SDL2_mixer )
target_link_libraries(Uno-2 PRIVATE Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Test )



add_custom_command(TARGET Uno-2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/libraries/bin"
        $<TARGET_FILE_DIR:Uno-2>)

add_custom_command(TARGET Uno-2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/sounds1"
        $<TARGET_FILE_DIR:Uno-2>)

    add_custom_command(TARGET Uno-2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/sounds1"
            $<TARGET_FILE_DIR:Uno-2>/sounds1)
