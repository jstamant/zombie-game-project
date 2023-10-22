cmake_minimum_required(VERSION 3.10.0)
project(sdl-app.out CXX)

message(STATUS "Project source directory is at ${PROJECT_SOURCE_DIR}")
message(STATUS "cmake binary directory is at ${CMAKE_BINARY_DIR}")
message(STATUS "cmake source directory is at ${CMAKE_SOURCE_DIR}")

# The binary needs to be adjacent to the assets, so this is set its location accordingly
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(SOURCES
  src/bullet.cpp
  src/entitymanager.cpp
  src/functions.cpp
  src/game.cpp
  src/inputsystem.cpp
  src/main.cpp
  src/physics.cpp
  src/rendersystem.cpp
  src/sprite.cpp
  src/subject.cpp
  src/velocity.cpp)

add_executable(sdl-app.out ${SOURCES})

include_directories(include)
target_link_libraries(sdl-app.out SDL2 SDL2_image)

add_custom_target(run
  COMMAND sdl-app.out
  DEPENDS sdl-app.out
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
