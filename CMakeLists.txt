#set gcc version first
SET(CMAKE_CXX_COMPILER g++)

## Compiler version check.
## Calling directly g++-x.y is a bad solution since some distros lack symlinks with version number.
execute_process(COMMAND         g++ -dumpversion
                COMMAND         tr -d .
                OUTPUT_VARIABLE GCC_VERSION
                OUTPUT_STRIP_TRAILING_WHITESPACE)

IF(${GCC_VERSION} LESS "46")
        MESSAGE(SEND_ERROR "gcc version must be >= 4.6")
ENDIF()

PROJECT(c++ml)

cmake_minimum_required(VERSION 2.6)

#QT Section
FIND_PACKAGE(Qt4 REQUIRED)

FIND_PACKAGE(Boost REQUIRED)


if (WIN32)
   SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Users/redpist/Downloads/boost_1_51_0")
   SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Users/redpist/Downloads/boost_1_51_0/libs")
endif (WIN32)

#Libraries Section
SET(${PROJECT_NAME}_LIB_DIRECTORY lib)
INCLUDE_DIRECTORIES(
                    )


#Headers
SET(${PROJECT_NAME}_HEADER_DIRECTORY include/)
INCLUDE_DIRECTORIES(
				   ${CMAKE_INCLUDE_PATH}
                   ${${PROJECT_NAME}_HEADER_DIRECTORY}
                   ${CMAKE_CURRENT_BINARY_DIR}
                   )
#Headers QT
INCLUDE(${QT_USE_FILE}
        )


#UI QT
SET(${PROJECT_NAME}_QTUI
        ui/MainWindow.ui
        ui/AboutWindow.ui
        ui/HelpWindow.ui
	      ui/ClassificatorProperty.ui)

# UI RESSOURCES
SET(${PROJECT_NAME}_RESOURCES ui/ressources.qrc)

QT4_ADD_RESOURCES(${PROJECT_NAME}_RCC ${${PROJECT_NAME}_RESOURCES})

#Sources
SET(${PROJECT_NAME}_SRC_DIRECTORY src/)
SET(${PROJECT_NAME}_SRCS
    ${${PROJECT_NAME}_SRC_DIRECTORY}/main.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/Inheritance.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/AST.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/ui/qt/main_w.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/ui/qt/diagram_scene.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/ui/qt/classificator_property_window.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/ui/qt/classificator_graphic_item.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/ui/qt/link_graphics_item.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/ui/qt/link_head_graphics_item.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/ui/qt/link_connection_graphics_item.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/classificator.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/meta_classificator.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/class.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/struct.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/union.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/members.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/link.cc
    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/dependency.cc
    )
#    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/arrow.cc
#    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/arrow_connection.cc
#    ${${PROJECT_NAME}_SRC_DIRECTORY}/object/dependency.cc

SET(CMAKE_CXX_FLAGS "-Wextra -Wall -std=c++0x -g3")

#QT Compilation
QT4_WRAP_UI(${PROJECT_NAME}_QTUI_HEADERS
        ${${PROJECT_NAME}_QTUI})

#QT Compilation
QT4_WRAP_CPP(${PROJECT_NAME}_QT_HEADERS_MOC
             ${${PROJECT_NAME}_HEADER_DIRECTORY}/ui/qt/main_w.h
             ${${PROJECT_NAME}_HEADER_DIRECTORY}/ui/qt/diagram_scene.hh
             ${${PROJECT_NAME}_HEADER_DIRECTORY}/ui/qt/classificator_graphic_item.hh
             ${${PROJECT_NAME}_HEADER_DIRECTORY}/ui/qt/classificator_property_window.hh
             ${${PROJECT_NAME}_HEADER_DIRECTORY}/ui/qt/link_graphics_item.hh
             ${${PROJECT_NAME}_HEADER_DIRECTORY}/ui/qt/link_connection_graphics_item.hh
             )

#        ${${PROJECT_NAME}_HEADER_DIRECTORY}/object/arrow.hh
#        ${${PROJECT_NAME}_HEADER_DIRECTORY}/object/arrow_connection.hh)

#Compilation Section
add_executable(${PROJECT_NAME}
              ${${PROJECT_NAME}_SRCS}
              ${${PROJECT_NAME}_QT_HEADERS_MOC}
              ${${PROJECT_NAME}_QTUI_HEADERS}
              ${${PROJECT_NAME}_RCC}
              )

#link section
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES})
