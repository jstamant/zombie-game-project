cmake_minimum_required(VERSION 3.10.0)
project(sdl-app.out CXX)

message(STATUS "$PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "$CMAKE_BINARY_DIR:   ${CMAKE_BINARY_DIR}")
message(STATUS "$CMAKE_SOURCE_DIR:   ${CMAKE_SOURCE_DIR}")

# Pulled from https://thatonegamedev.com/cpp/programming-a-c-game-for-the-web-emscripten/
if (EMSCRIPTEN)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

message(STATUS "$CMAKE_EXECUTABLE_SUFFIX: ${CMAKE_EXECUTABLE_SUFFIX}")
message(STATUS "$EMSCRIPTEN: ${EMSCRIPTEN}")

# The binary needs to be adjacent to the assets, so this is set its location accordingly
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(SOURCES
  src/entitymanager.cpp
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
target_link_libraries(sdl-app.out SDL2 SDL2_image SDL2_ttf)

add_custom_target(run
  COMMAND sdl-app.out
  DEPENDS sdl-app.out
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
