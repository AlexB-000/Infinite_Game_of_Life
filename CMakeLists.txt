cmake_minimum_required(VERSION 3.28)
project(Infinite_Game_of_Life LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts
    DESTINATION ${CMAKE_BINARY_DIR}/bin)

add_executable(inf_game_of_life src/main.cpp)
target_sources(inf_game_of_life
PRIVATE
    src/events.cpp
)
target_compile_features(inf_game_of_life PRIVATE cxx_std_17)
target_link_libraries(inf_game_of_life PRIVATE SFML::Graphics)
target_compile_options(inf_game_of_life PRIVATE -O3)
