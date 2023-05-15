main: main.cpp game.h game.cpp
	g++ -o main main.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
