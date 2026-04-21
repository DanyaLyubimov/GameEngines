cmake_minimum_required(VERSION 3.10.0)
project(GameDev VERSION 0.1.0 LANGUAGES C CXX)

add_executable(GameDev main.cpp)

set(SFML_VERSION 3.0.0)

include(FetchContent)

FetchContent_Declare(
  SFML
  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

target_link_libraries(GameDev PRIVATE sfml-window sfml-graphics sfml-system)