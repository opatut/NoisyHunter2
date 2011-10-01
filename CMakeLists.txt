cmake_minimum_required(VERSION 2.8.0)

project(NoisyHunter)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/")
set(QT_DONT_USE_QTGUI TRUE)
set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(SFML 2 COMPONENTS audio graphics network system window REQUIRED)
find_package(Qt4 REQUIRED)
find_package(Bullet REQUIRED)

add_definitions("-Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-but-set-parameter -g -pedantic -fPIC -std=c++0x")
add_definitions("-DDEBUG")
add_definitions(${QT_DEFINITIONS})
include(${QT_USE_FILE})

include_directories(
	"${CMAKE_SOURCE_DIR}/src/"
	${SFML_INCLUDE_DIRS}
	${BULLET_INCLUDE_DIRS}
)

file(GLOB_RECURSE sources src/*.cpp)
#AUX_SOURCE_DIRECTORY(src/ sources)

add_executable(NoisyHunter
    ${sources})
    
target_link_libraries(NoisyHunter
    ${SFML_LIBRARIES}
    ${QT_LIBRARIES}
    ${BULLET_LIBRARIES}
    )
