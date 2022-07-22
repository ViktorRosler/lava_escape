cmake_minimum_required(VERSION 3.17)
project(game)

set(CMAKE_CXX_STANDARD 17)

set(SFML_MODULES graphics window system)

foreach(i ${SFML_MODULES})
    list(APPEND SFML_LIBRARIES "sfml-${i}")
endforeach(i)

set(SOURCE_FILES main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(game main.cpp state.cpp state.h game_state.cpp game_state.h level.cpp level.h menu_state.cpp menu_state.h game_object.h moving_object.cpp moving_object.h enemy.cpp enemy.h projectile.cpp projectile.h player.cpp player.h level_loader.cpp level_loader.h textured_object.h textured_object.cpp constants.h animated_object.cpp animated_object.h lava.cpp lava.h walking_enemy.h walking_enemy.cpp jumping_enemy.cpp jumping_enemy.h flying_enemy.cpp flying_enemy.h)

target_link_libraries(game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
