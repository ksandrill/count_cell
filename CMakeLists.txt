cmake_minimum_required(VERSION 3.20)
project(cell_count)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP REQUIRED)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt_lib/6.1.3/mingw81_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

add_executable(cell_count main.cpp image_processing/imageProcessing.cpp image_processing/imageProcessing.h image_processing/morphology.cpp image_processing/morphology.h
        image_processing/algorithms/filters.h image_processing/algorithms/filters.cpp image_processing/algorithms/algorithms.h image_processing/algorithms/algorithms.cpp)
target_link_libraries(cell_count
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        OpenMP::OpenMP_CXX
        )

if (WIN32)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/imageformats")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${QT_INSTALL_PATH}/plugins/imageformats/"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/imageformats")
    endif ()
    foreach (QT_LIB Core Gui Widgets Charts)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

