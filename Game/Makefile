CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17


# type 'make all' or 'gmake all' to build everything
all: game

game: main.o state.o game_state.o menu_state.o level.o textured_object.o animated_object.o lava.o moving_object.o player.o enemy.o projectile.o level_loader.o walking_enemy.o flying_enemy.o jumping_enemy.o -lsfml-window -lsfml-graphics -lsfml-system

	$(CXX) $^ $(LDFLAGS) -o $@

# to build an *.o file we need corresponding *.cc file
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

# to clean up compiler-generated files
clean:
	\rm -f *.o *.stackdump game

