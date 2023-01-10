cmake_minimum_required(VERSION 3.23.2)
project(HelloSFML)
set(CMAKE_CXX_STANDARD 17)
add_executable(HelloSFML main.cpp Button.cpp Button.h Card.cpp Card.h Game.cpp Game.h Icon_file.rc)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-audio)
