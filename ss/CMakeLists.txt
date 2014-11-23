cmake_minimum_required(VERSION 2.6)
project(GAME)

if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(GAME_VERSION_MAJOR 1)
set(GAME_VERSION_MINOR 0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

configure_file(
	"${PROJECT_SOURCE_DIR}/build/config.h.in"
	"${PROJECT_BINARY_DIR}/build/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

set(EXECUTABLE_NAME "GAME")
add_executable(${EXECUTABLE_NAME} main.cpp Game.cpp qsfmlcanvas.cpp)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(Qt5Widgets)

find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/build/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${GAME_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${GAME_VERSION_MINOR}")
include(CPack)
