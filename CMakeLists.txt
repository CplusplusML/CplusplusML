#set gcc version first
SET(CMAKE_CXX_COMPILER g++-4.6)

PROJECT(c++ml)

cmake_minimum_required(VERSION 2.6)

#QT Section
FIND_PACKAGE(Qt4 REQUIRED)

#Libraries Section
SET(${PROJECT_NAME}_LIB_DIRECTORY lib)
INCLUDE_DIRECTORIES(
										)


#Headers
SET(${PROJECT_NAME}_HEADER_DIRECTORY include/)
INCLUDE_DIRECTORIES(
									 ${${PROJECT_NAME}_HEADER_DIRECTORY}
									 ${CMAKE_CURRENT_BINARY_DIR}
									 )
#Headers QT
INCLUDE(${QT_USE_FILE})


#UI QT
SET(${PROJECT_NAME}_QTUI
				ui/MainWindow.ui)

#UI RESSOURCES
 SET(${PROJECT_NAME}_RESOURCES
				ressource.qrc)

#Sources
SET(${PROJECT_NAME}_SRC_DIRECTORY src/)
SET(${PROJECT_NAME}_SRCS
    ${${PROJECT_NAME}_SRC_DIRECTORY}/main.cpp
    ${${PROJECT_NAME}_SRC_DIRECTORY}/arrow.cpp
    ${${PROJECT_NAME}_SRC_DIRECTORY}/diagramitem.cpp
    ${${PROJECT_NAME}_SRC_DIRECTORY}/diagramscene.cpp
    ${${PROJECT_NAME}_SRC_DIRECTORY}/diagramtextitem.cpp
    ${${PROJECT_NAME}_SRC_DIRECTORY}/main.cpp
    ${${PROJECT_NAME}_SRC_DIRECTORY}/mainwindow.cpp
		)

QT4_ADD_RESOURCES(${PROJECT_NAME}_RESOURCES_RCC ${PROJECT_NAME}_RESOURCES)

SET(CMAKE_CXX_FLAGS "-Wextra -Wall -std=c++0x")

#QT Compilation
QT4_WRAP_UI(${PROJECT_NAME}_QTUI_HEADERS
				${${PROJECT_NAME}_QTUI})

#Compilation Section
add_executable(${PROJECT_NAME}
							${${PROJECT_NAME}_SRCS}
							${${PROJECT_NAME}_QTUI_HEADERS}
              ${PROJECT_NAME}_RESOURCES_RCC
							)

#link section
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES})
